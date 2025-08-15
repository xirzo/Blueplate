#include "configuration.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#define TOML_EXCEPTIONS 0
#define TOML_IMPLEMENTATION
#include <toml++/toml.h>
#include <vector>

namespace pc {

static void write_file(const fs::path &path, const std::string &content) {
    std::ofstream file(path);

    if (!file) {
        throw fs::filesystem_error(
            "Failed to create file: " + path.string(), std::error_code()
        );
    }

    file << content;
}

std::optional<fs::path> get_config_path() {
    fs::path config_path;

#if defined(_WIN32)
    if (const char *appdata = std::getenv("APPDATA")) {
        config_path = fs::path(appdata) / APP_NAME;
        return config_path;
    }
#elif defined(__APPLE__)
    if (const char *home = std::getenv("HOME")) {
        config_path =
            fs::path(home) / "Library" / "Application Support" / APP_NAME;
        return config_path;
    }
#else
    if (const char *xdg_config = std::getenv("XDG_CONFIG_HOME")) {
        config_path = fs::path(xdg_config) / APP_NAME;
        return config_path;
    }

    if (const char *home = std::getenv("HOME")) {
        config_path = fs::path(home) / ".config" / APP_NAME;
        return config_path;
    }
#endif

    return std::nullopt;
}

std::optional<std::vector<KeyValue>> get_config_variables() {
    auto config_path = get_config_path();

    if (!config_path) {
        return std::nullopt;
    }

    fs::path configuration_path = *config_path / CONFIG_FILE_NAME;

    toml::parse_result parsed;

    try {
        parsed = toml::parse_file(configuration_path.string());
    } catch (const toml::parse_error &) {
        return std::nullopt;
    }
    if (!parsed) {
        return std::nullopt;
    }

    toml::table &root = parsed.table();

    toml::node_view vars_view = root["variables"]["custom"];

    if (!vars_view || !vars_view.is_array()) {
        return std::nullopt;
    }

    const toml::array    &arr = *vars_view.as_array();
    std::vector<KeyValue> result;
    result.reserve(arr.size());

    for (const toml::node &node : arr) {
        const toml::array *key_value = node.as_array();

        if (!key_value || key_value->size() != 2) {
            continue;
        }

        auto key = (*key_value)[0].as_string();
        auto value = (*key_value)[1].as_string();

        if (!key || !value) {
            continue;
        }

        result.push_back({ key->get(), value->get() });
    }

    return result;
}

std::expected<void, std::string> create_sample_config() {
    auto config_path = get_config_path();

    if (!config_path) {
        return std::unexpected("Failed to get config path");
    }

    if (fs::exists(*config_path)) {
        return std::unexpected(
            "Config already exists: " + config_path->string()
        );
    }

    try {
        const fs::path template_path = *config_path / "templates";
        const fs::path project_path = template_path / "sample-cmake-cpp";

        fs::create_directory(*config_path);

        toml::table config_table{
            { "variables",
              toml::table{
                  { "custom",
                    toml::array{ toml::array{ "pc_version", "1.0.1" },
                                 toml::array{ "pc_author", "xirzo" } } } } }
        };

        std::ostringstream oss;
        oss << toml::default_formatter{ config_table };

        write_file(*config_path / CONFIG_FILE_NAME, oss.str());

        fs::create_directory(template_path);
        fs::create_directory(project_path);

        fs::create_directory(project_path / "src");
        fs::create_directory(project_path / "include");

        write_file(
            project_path / "CMakeLists.txt",
            R"(cmake_minimum_required(VERSION 3.24.1)
project(${pc_project_name} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(${PROJECT_NAME} 
    src/main.cpp
)
)"
        );

        write_file(project_path / "src" / "main.cpp", R"(#include <iostream>
#include "${pc_project_name}.h"

int main() {
    std::cout << "Hello from ${pc_project_name}!" << std::endl;
    example_function();
    return 0;
}
)");

        write_file(
            project_path / "include" / "${pc_project_name}.h", R"(#pragma once

#include <iostream>

inline void example_function() {
    std::cout << "This is an example function from ${pc_project_name}" << std::endl;
}
)"
        );

        return {};
    } catch (const fs::filesystem_error &e) {
        try {
            if (fs::exists(*config_path)) {
                fs::remove_all(*config_path);
            }
        } catch (...) {}
        return std::unexpected(std::string("Filesystem error: ") + e.what());
    }
}

}  // namespace pc
