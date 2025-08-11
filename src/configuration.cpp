#include "configuration.h"

#include <vector>

namespace pc {

constexpr std::string APP_NAME = "blueplate";

std::optional<fs::path> get_templates_directory() {
    fs::path templates_path;

#if defined(_WIN32)
    if (const char *appdata = std::getenv("APPDATA")) {
        templates_path = fs::path(appdata) / APP_NAME / "templates";
    }
#elif defined(__APPLE__)
    if (const char *home = std::getenv("HOME")) {
        templates_path = fs::path(home) / "Library" / "Application Support"
                       / APP_NAME / "templates";
    }
#else
    if (const char *home = std::getenv("HOME")) {
        templates_path = fs::path(home) / ".config" / APP_NAME / "templates";
    }

    if (!fs::exists(templates_path)) {
        if (const char *xdg_config = std::getenv("XDG_CONFIG_HOME")) {
            templates_path = fs::path(xdg_config) / APP_NAME / "templates";
        }
    }
#endif

    std::vector<fs::path> fallbacks = {
        fs::current_path() / "templates",

#if defined(_WIN32)
        fs::path(
            std::getenv("ProgramFiles") ? std::getenv("ProgramFiles")
                                        : "C:\\Program Files"
        ) / APP_NAME
            / "templates",
#else
        "/usr/local/share/" + APP_NAME + "/templates",
        "/usr/share/" + APP_NAME + "/templates",
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
}  // namespace pc
