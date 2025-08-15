#include "key_inserter.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

namespace pc {

std::string replace_keys_in_string(std::string str, const Keys &keys) {
    for (const auto &[key, value] : keys) {
        std::string placeholder = "${" + key + "}";

        std::string::size_type pos = 0;

        while ((pos = str.find(placeholder, pos)) != std::string::npos) {
            str.replace(pos, placeholder.length(), value);
            pos += value.length();
        }
    }
    return str;
}

std::expected<void, std::string>
replace_file_keys(fs::path file_path, const Keys &keys) {
    std::string original_filename = file_path.filename().string();
    std::string new_filename = replace_keys_in_string(original_filename, keys);

    fs::path new_path = file_path.parent_path() / new_filename;
    fs::path temp_path = file_path.parent_path() / (new_filename + ".tmp");

    if (new_filename != original_filename && fs::exists(new_path)) {
        return std::unexpected(
            "Cannot rename file: destination already exists: "
            + new_path.string()
        );
    }

    std::ifstream input(file_path);

    if (!input) {
        return std::unexpected(
            "Failed to open file for read: " + file_path.string()
        );
    }

    std::ofstream output(temp_path);
    if (!output) {
        return std::unexpected(
            "Failed to create temporary file: " + temp_path.string()
        );
    }

    std::string line;
    while (std::getline(input, line)) {
        line = replace_keys_in_string(line, keys);
        output << line << '\n';
    }

    input.close();
    output.close();

    if (input.bad()) {
        fs::remove(temp_path);
        return std::unexpected(
            "Error reading from file: " + file_path.string()
        );
    }

    if (output.bad()) {
        fs::remove(temp_path);
        return std::unexpected("Error writing to temporary file");
    }

    try {
        fs::remove(file_path);

        if (new_filename != original_filename) {
            fs::rename(temp_path, new_path);
        } else {
            fs::rename(temp_path, file_path);
        }
    } catch (const fs::filesystem_error &e) {
        return std::unexpected(
            "Failed to replace/rename file: " + std::string(e.what())
        );
    }

    return {};
}

std::expected<void, std::string>
replace_directory_keys(fs::path dir_path, const Keys &keys, bool recursive) {
    if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
        return std::unexpected("Invalid directory path: " + dir_path.string());
    }

    std::vector<fs::path> paths_to_process;

    for (const auto &entry : fs::directory_iterator(dir_path)) {
        paths_to_process.push_back(entry.path());
    }

    for (const auto &path : paths_to_process) {
        if (fs::is_directory(path) && recursive) {
            auto result = replace_directory_keys(path, keys, true);

            if (!result) {
                return result;
            }

            std::string dir_name = path.filename().string();
            std::string new_dir_name = replace_keys_in_string(dir_name, keys);

            if (dir_name != new_dir_name) {
                fs::path new_path = path.parent_path() / new_dir_name;

                try {
                    fs::rename(path, new_path);
                } catch (const fs::filesystem_error &e) {
                    return std::unexpected(
                        "Failed to rename directory: " + std::string(e.what())
                    );
                }
            }
        } else if (fs::is_regular_file(path)) {
            auto result = replace_file_keys(path, keys);

            if (!result) {
                return result;
            }
        }
    }

    return {};
}

}  // namespace pc
