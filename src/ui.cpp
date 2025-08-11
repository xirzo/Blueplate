#include "ui.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

std::string run_selector(
    const std::vector<std::string> &options,
    const std::string              &description
) {
    int  selected_id = 0;
    bool has_cancelled = false;
    bool has_confirmed = false;

    auto component = Menu(&options, &selected_id);

    auto ui = Renderer(component, [&] {
        return vbox(
                   {
                       text(description) | bold,
                       separator(),
                       component->Render() | frame,
                       separator(),
                       text(
                           "Up/Down or j/k to move, Enter to confirm, q to cancel"
                       ) | dim,
                   }
               )
             | border;
    });

    auto with_keys = CatchEvent(ui, [&](Event event) {
        if (event == Event::ArrowDown || event == Event::Character('j')) {
            selected_id = (selected_id + 1) % (int)options.size();
            return true;
        }
        if (event == Event::ArrowUp || event == Event::Character('k')) {
            selected_id =
                (selected_id - 1 + (int)options.size()) % (int)options.size();
            return true;
        }
        return false;
    });

    auto screen = ScreenInteractive::TerminalOutput();

    screen.Loop(CatchEvent(with_keys, [&](Event event) {
        if (has_cancelled) {
            screen.ExitLoopClosure()();
            return true;
        }
        if (has_confirmed) {
            screen.ExitLoopClosure()();
            return true;
        }

        if (event == Event::Character('q') || event == Event::Escape) {
            has_cancelled = true;
            screen.ExitLoopClosure()();
            return true;
        }
        if (event == Event::Return) {
            has_confirmed = true;
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    }));

    if (has_cancelled) {
        return {};
    }

    if (!has_confirmed) {
        return {};
    }

    return options[selected_id];
}
