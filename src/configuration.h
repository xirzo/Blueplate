#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <expected>
#include <optional>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace pc {

constexpr char CONFIG_FILE_NAME[] = "configuration.toml";

std::optional<fs::path> get_config_path();

std::expected<void, std::string> create_sample_config(
    const fs::path &config_path,
    const fs::path &template_path
);

}  // namespace pc

#endif  // CONFIGURATION_H
