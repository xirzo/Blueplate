#ifndef PROJECT_CREATOR_H
#define PROJECT_CREATOR_H

#include <optional>
#include <expected>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace pc {

std::optional<fs::path> get_templates_directory();

std::expected<void, std::string> create_project(
    const std::string &project_name,
    const std::string &template_name,
    const fs::path    &path = fs::current_path()
);

}  // namespace pc

#endif  // !PROJECT_CREATOR_H
