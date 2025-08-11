#ifndef UI_H
#define UI_H



    // auto screen = ScreenInteractive::TerminalOutput();
    //
    // int counter = 0;
    //
    // auto component = Container::Vertical({
    //     Button("Increment", [&]{ counter++; }),
    //     Button("Quit", [&]{ screen.Exit(); }),
    // });
    //
    // auto renderer = Renderer(component, [&]{
    //     return vbox({
    //         text("Hello from FTXUI") | bold,
    //         separator(),
    //         text("Counter: " + std::to_string(counter)),
    //         separator(),
    //         hbox({
    //             text("[Increment]"),
    //             text("  "),
    //             text("[Quit]"),
    //         }) | dim,
    //     }) | border;
    // });
    //
    // screen.Loop(renderer);

#endif // !UI_H
