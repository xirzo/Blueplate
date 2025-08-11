#include "app.h"
#include <filesystem>
#include <ranges>

#include "CLI11.hpp"
#include "project_creator.h"
#include "ui.h"

namespace fs = std::filesystem;

namespace pc {

static CLI::App    s_App{ "CLI tool for fast creating of new projects" };
static std::string s_ProjectName{};

int run_app(int argc, char **argv) {
    argv = s_App.ensure_utf8(argv);

    CLI::App *create = s_App.add_subcommand("create", "Create a new project");

    create->add_option("name", s_ProjectName, "Project name")->required();

    create->callback([&]() {
        std::optional<fs::path> template_path = get_templates_directory();

        if (!template_path) {
            std::cerr << "Could not find template directory" << std::endl;
            return;
        }

        std::vector<std::string> names =
            fs::directory_iterator(*template_path)
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
