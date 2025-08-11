#include "configuration.h"

#include <filesystem>
#include <iostream>
#include <fstream>

namespace pc {

constexpr std::string APP_NAME = "blueplate";

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

void write_file(const fs::path &path, const std::string &content) {
    std::ofstream file(path);

    if (!file) {
        throw fs::filesystem_error(
            "Failed to create file: " + path.string(), std::error_code()
        );
    }

    file << content;
}

std::expected<void, std::string> create_sample_config(
    const fs::path &config_path,
    const fs::path &template_path
) {
    if (fs::exists(config_path)) {
        return std::unexpected(
            "Config already exists: " + config_path.string()
        );
    }

    try {
        const fs::path project_path = template_path / "sample-cmake-cpp";
        fs::create_directory(config_path);
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
            if (fs::exists(config_path)) {
                fs::remove_all(config_path);
            }
        } catch (...) {}
        return std::unexpected(std::string("Filesystem error: ") + e.what());
    }
}

}  // namespace pc
