#ifndef PROJECT_CREATOR_H
#define PROJECT_CREATOR_H

#include <expected>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace pc {

std::expected<void, std::string> create_project(
    const std::string &project_name,
    const std::string &template_name,
    const fs::path    &templates_path,
    const fs::path    &path
);

}  // namespace pc

#endif  // !PROJECT_CREATOR_H
