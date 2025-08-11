#include "app.h"
#include <filesystem>
#include <ranges>

#include "CLI11.hpp"
#include "project_creator.h"
#include "configuration.h"
#include "ui.h"

namespace fs = std::filesystem;

namespace pc {

static CLI::App    s_App{ "CLI tool for fast creating of new projects" };
static std::string s_ProjectName{};
static fs::path    s_ConfigPath{};
static fs::path    s_TemplatePath{};

int run_app(int argc, char **argv) {
    argv = s_App.ensure_utf8(argv);

    std::optional<fs::path> config_path = get_config_path();

    if (!config_path) {
        std::cerr << "Could not find config directory" << std::endl;
    } else {
        s_ConfigPath = config_path.value();
        s_TemplatePath = s_ConfigPath / "templates";
    }

    CLI::App *config = s_App.add_subcommand("config", "Interact with config");

    CLI::App *create_config =
        config->add_subcommand("create", "Create a sample config");

    create_config->callback([&]() {

    });

    CLI::App *delete_config =
        config->add_subcommand("delete", "Delete your existing config");

    // TODO: implement config commands

    CLI::App *create = s_App.add_subcommand("create", "Create a new project");

    create->add_option("name", s_ProjectName, "Project name")->required();

    create->callback([&]() {
        if (s_TemplatePath.empty()) {
            std::cerr << "Could not find template directory, cannot proceed"
                      << std::endl;
            return;
        }

        std::vector<std::string> names =
            fs::directory_iterator(s_TemplatePath)
            | std::views::transform([](fs::directory_entry const &entry) {
                  return entry.path().filename();
              })
            | std::ranges::to<std::vector<std::string>>();

        if (names.empty()) {
            std::cerr << "There are no templates in config directory"
                      << std::endl;
        }

        std::string chosen_template =
            run_selector(names, "Select a project template");

        if (chosen_template.empty()) {
            return;
        }

        std::expected<void, std::string> create_result =
            create_project(s_ProjectName, chosen_template);

        if (!create_result) {
            std::cerr << create_result.error() << std::endl;
            return;
        }
    });

    try {
        s_App.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return s_App.exit(e);
    }

    return 0;
}

}  // namespace pc
