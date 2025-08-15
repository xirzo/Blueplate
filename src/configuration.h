#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <expected>
#include <optional>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace pc {

struct KeyValue {
    std::string key;
    std::string value;
};

constexpr char APP_NAME[] = "blueplate";
constexpr char CONFIG_FILE_NAME[] = "configuration.toml";

std::optional<fs::path>              get_config_path();
std::optional<std::vector<KeyValue>> get_config_variables();
std::expected<void, std::string>     create_sample_config();

}  // namespace pc

#endif  // CONFIGURATION_H
