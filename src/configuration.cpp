#include "configuration.h"

#include <vector>

namespace pc {

constexpr std::string APP_NAME = "blueplate";

std::optional<fs::path> get_config_path() {
    fs::path config_path;

#if defined(_WIN32)
    if (const char *appdata = std::getenv("APPDATA")) {
        config_path = fs::path(appdata) / APP_NAME;
    }
#elif defined(__APPLE__)
    if (const char *home = std::getenv("HOME")) {
        config_path =
            fs::path(home) / "Library" / "Application Support" / APP_NAME;
    }
#else
    if (const char *home = std::getenv("HOME")) {
        config_path = fs::path(home) / ".config" / APP_NAME;
    }

    if (!fs::exists(config_path)) {
        if (const char *xdg_config = std::getenv("XDG_CONFIG_HOME")) {
            config_path = fs::path(xdg_config) / APP_NAME;
        }
    }
#endif

    std::vector<fs::path> fallbacks = {
        fs::current_path(),

#if defined(_WIN32)
        fs::path(
            std::getenv("ProgramFiles") ? std::getenv("ProgramFiles")
                                        : "C:\\Program Files"
        ) / APP_NAME,
#else
        "/usr/local/share/" + APP_NAME,
        "/usr/share/" + APP_NAME,
#endif
    };

    if (fs::exists(config_path)) {
        return config_path;
    }

    for (const auto &path : fallbacks) {
        if (fs::exists(path)) {
            return path;
        }
    }

    return std::nullopt;
}

std::optional<fs::path> get_templates_directory() {
    std::optional<fs::path> config_path = get_config_path();

    if (!config_path) {
        return std::nullopt;
    }

    return *config_path / "templates";
}

std::expected<void, std::string> create_sample_config() {
    return {};
}

}  // namespace pc
