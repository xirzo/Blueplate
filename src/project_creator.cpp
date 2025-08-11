#include "project_creator.h"
#include <iostream>
#include <optional>
#include <vector>

namespace pc {

std::optional<fs::path> get_templates_directory() {
    fs::path templates_path;

#if defined(_WIN32)
    if (const char *appdata = std::getenv("APPDATA")) {
        templates_path = fs::path(appdata) / "project-creator" / "templates";
    }
#elif defined(__APPLE__)
    if (const char *home = std::getenv("HOME")) {
        templates_path = fs::path(home) / "Library" / "Application Support"
                       / "project-creator" / "templates";
    }
#else
    if (const char *home = std::getenv("HOME")) {
        templates_path =
            fs::path(home) / ".config" / "project-creator" / "templates";
    }

    if (!fs::exists(templates_path)) {
        if (const char *xdg_config = std::getenv("XDG_CONFIG_HOME")) {
            templates_path =
                fs::path(xdg_config) / "project-creator" / "templates";
        }
    }
#endif

    std::vector<fs::path> fallbacks = {
        fs::current_path() / "templates",

#if defined(_WIN32)
        fs::path(
            std::getenv("ProgramFiles") ? std::getenv("ProgramFiles")
                                        : "C:\\Program Files"
        ) / "project-creator"
            / "templates",
#else
        "/usr/local/share/project-creator/templates",
        "/usr/share/project-creator/templates",
#endif
    };

    if (fs::exists(templates_path)) {
        return templates_path;
    }

    for (const auto &path : fallbacks) {
        if (fs::exists(path)) {
            return path;
        }
    }

    return std::nullopt;
}

std::expected<void, std::string> create_project(
    const std::string &project_name,
    const std::string &template_name,
    const fs::path    &path
) {
    std::optional<fs::path> templates_directory = get_templates_directory();

    if (!templates_directory) {
        return std::unexpected("No templates directory found");
    }

    fs::path template_directory = *templates_directory / template_name;

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
