#include "app.h"

#include "CLI11.hpp"
#include "project_creator.h"
#include "ui.h"

namespace pc {

static CLI::App    s_App{ "CLI tool for fast creating of new projects" };
static std::string s_ProjectName{};

int run_app(int argc, char **argv) {
    argv = s_App.ensure_utf8(argv);

    CLI::App *create = s_App.add_subcommand("create", "Create a new project");

    create->add_option("name", s_ProjectName, "Project name")->required();

    create->callback([&]() {
        std::string chosen_template;

        chosen_template = run_selector(
            { "C++ Meson", "C Meson", "C++ CMake", "C CMake" },
            "Select a project template"
        );

        if (chosen_template.empty()) {
            return;
        }

        create_project(s_ProjectName, chosen_template);
    });

    try {
        s_App.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return s_App.exit(e);
    }

    return 0;
}

}  // namespace pc
