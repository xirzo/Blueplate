# Blueplate

Blueplate is a small cross‑platform TUI helper to scaffold a new project from one of your local templates.

## Dependencies
- C++23 compiler
- Meson + Ninja
- [FTXUI](https://github.com/ArthurSonzogni/FTXUI)
- CLI11 (already in files)

## Build & Run
```bash
git clone https://github.com/xirzo/blueplate
cd blueplate

meson setup build
meson compile -C build

./build/blueplate --help
./build/blueplate create my-app
```

If you want to use **blueplate** in any directory you want, you may install it with meson inside build directory

```bash
meson install
```

## Adding Templates

Create a templates directory (choose the one that matches your OS):

Platform | Path
-------- | ----
Linux (XDG) | $XDG_CONFIG_HOME/blueplate/templates
Linux (fallback) | $HOME/.config/blueplate/templates
macOS | $HOME/Library/Application Support/blueplate/templates
Windows | %APPDATA%\blueplate\templates

Each subdirectory of `CONFIG_DIRECTORY/templates` is a one separate template.

Example (Linux):
```bash
mkdir -p ~/.config/blueplate/templates/basic-cpp/src
cat > ~/.config/blueplate/templates/basic-cpp/src/main.cpp <<'EOF'
#include <iostream>
int main(){ std::cout << "Hello from basic-cpp!\\n"; }
EOF
```

Now run:

```bash
./build/blueplate create test-app
```

## Controls

Key | Action
--- | ------
Up / k | Up
Down / j | Down
Enter | Confirm
q / Esc | Cancel
