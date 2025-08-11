#include "project_creator.h"
#include <iostream>
#include <optional>

#include "configuration.h"

namespace pc {

std::expected<void, std::string> create_project(
    const std::string &project_name,
    const std::string &template_name,
    const fs::path    &templates_path,
    const fs::path    &path
) {
    fs::path template_directory = templates_path / template_name;

    if (!fs::exists(template_directory)
        || !fs::is_directory(template_directory)) {
        return std::unexpected("Template '" + template_name + "' not found");
    }

    fs::path project_directory = path / project_name;

    if (fs::exists(project_directory)) {
        return std::unexpected(
            "Project directory '" + project_directory.string()
            + "' already exists"
        );
    }

    try {
        std::cout << "Creating project '" << project_name << "' with template '"
                  << template_name << "'" << std::endl;

        fs::create_directories(project_directory);

        fs::copy(
            template_directory,
            project_directory,
            fs::copy_options::recursive | fs::copy_options::copy_symlinks
        );

        return {};
    } catch (const fs::filesystem_error &e) {
        try {
            if (fs::exists(project_directory)) {
                fs::remove_all(project_directory);
            }
        } catch (...) {}

        return std::unexpected(std::string("Filesystem error: ") + e.what());
    }
}

}  // namespace pc
