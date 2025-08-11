#ifndef KEY_INSERTER_H
#define KEY_INSERTER_H

#include <expected>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

using Keys = std::unordered_map<std::string, std::string>;

namespace pc {

static Keys s_Keys;

void        set_key(const std::string key_name, const std::string value);
std::string replace_keys_in_string(std::string str);
std::expected<void, std::string> replace_file_keys(fs::path file_path);
std::expected<void, std::string>
replace_directory_keys(fs::path dir_path, bool recursive = true);

}  // namespace pc

#endif  // !KEY_INSERTER_H
