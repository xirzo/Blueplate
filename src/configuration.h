#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <optional>
#include <filesystem>

namespace fs = std::filesystem;

namespace pc {

std::optional<fs::path> get_templates_directory();
}

#endif  // CONFIGURATION_H
