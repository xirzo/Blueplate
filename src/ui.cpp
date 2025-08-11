#include "ui.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

std::string run_selector(
    const std::vector<std::string> &options,
    const std::string              &description
) {
    int  selected = 0;
    bool cancelled = false;
    bool confirmed = false;

    auto component = Menu(&options, &selected);

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
            selected = (selected + 1) % (int)options.size();
            return true;
        }
        if (event == Event::ArrowUp || event == Event::Character('k')) {
            selected =
                (selected - 1 + (int)options.size()) % (int)options.size();
            return true;
        }
        if (event == Event::Character('q') || event == Event::Escape) {
            cancelled = true;
            return true;
        }
        if (event == Event::Return) {
            confirmed = true;
            return true;
        }
        return false;
    });

    auto screen = ScreenInteractive::TerminalOutput();

    screen.Loop(CatchEvent(with_keys, [&](Event event) {
        if (cancelled) {
            screen.ExitLoopClosure()();
            return true;
        }
        if (confirmed) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    }));

    if (cancelled) {
        return {};
    }

    return options[selected];
}
