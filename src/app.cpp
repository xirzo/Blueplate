#include "app.h"
#include <filesystem>
#include <ranges>

#include <CLI/CLI.hpp>
#include "key_inserter.h"
#include "project_creator.h"
#include "configuration.h"
#include "ui.h"

namespace fs = std::filesystem;

namespace pc {

static CLI::App    s_App{ "CLI tool for fast creating of new projects" };
static std::string s_ProjectName{};
static std::string s_ChosenTemplate{};
static fs::path    s_ConfigPath{};
static fs::path    s_TemplatePath{};
static Keys        s_Keys{};

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
        std::expected<void, std::string> create_result = create_sample_config();

        if (!create_result) {
            std::cerr << create_result.error() << std::endl;
            return;
        }

        std::cout << "Succesfully created a sample config at " << s_ConfigPath
                  << std::endl;
    });

    CLI::App *delete_config =
        config->add_subcommand("remove", "remove your existing config");

    delete_config->callback([&]() {
        fs::remove_all(s_ConfigPath);
        std::cout << "Config removed at " << s_ConfigPath << std::endl;
    });

    CLI::App *create = s_App.add_subcommand("create", "Create a new project");

    create->add_option(
        "-t,--template",
        s_ChosenTemplate,
        "Template name (allows non-interactive use)"
    );

    create->add_option("name", s_ProjectName, "Project name")->required();

    create->callback([&]() {
        if (!fs::exists(s_TemplatePath)) {
            std::cerr << "Templates config directory does not exist"
                      << std::endl;
            return;
        }

        std::vector<std::string> names =
            fs::directory_iterator(s_TemplatePath)
            | std::views::transform([](fs::directory_entry const &entry) {
                  return entry.path().filename().string();
              })
            | std::ranges::to<std::vector<std::string>>();

        if (names.empty()) {
            std::cerr << "There are no templates in config directory"
                      << std::endl;
        }

        if (s_ChosenTemplate.empty()) {
            s_ChosenTemplate = run_selector(names, "Select a project template");
        }

        if (s_ChosenTemplate.empty()) {
            return;
        }

        std::expected<void, std::string> create_result = create_project(
            s_ProjectName, s_ChosenTemplate, s_TemplatePath, fs::current_path()
        );

        if (!create_result) {
            std::cerr << create_result.error() << std::endl;
            return;
        }

        s_Keys["pc_project_name"] = s_ProjectName;

        auto replace_result =
            replace_directory_keys(fs::current_path() / s_ProjectName, s_Keys);

        if (!replace_result) {
            std::cerr << replace_result.error() << std::endl;
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
