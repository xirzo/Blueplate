#ifndef KEY_INSERTER_H
#define KEY_INSERTER_H

#include <expected>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

using Keys = std::unordered_map<std::string, std::string>;

namespace pc {

std::string replace_keys_in_string(std::string str, const Keys &keys);
std::expected<void, std::string>
replace_file_keys(fs::path file_path, const Keys &keys);
std::expected<void, std::string> replace_directory_keys(
    fs::path    dir_path,
    const Keys &keys,
    bool        recursive = true
);

}  // namespace pc

#endif  // !KEY_INSERTER_H
