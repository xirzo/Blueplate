#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <expected>
#include <optional>
#include <filesystem>

namespace fs = std::filesystem;

namespace pc {

std::optional<fs::path> get_config_path();

std::expected<void, std::string> create_sample_config(
    const fs::path &template_path
);

}  // namespace pc

#endif  // CONFIGURATION_H
