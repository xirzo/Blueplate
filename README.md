# Blueplate

Blueplate is a small cross‑platform TUI helper to scaffold a new project from one of your local templates. It was tested on **Windows 10** (using *MinGW 15.1.0*) and **Linux**.

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

## Template Variables

Blueplate supports template variables in file contents and filenames. Variables use the `${variable_name}` syntax and are automatically replaced when creating a new project.

- `${pc_project_name}` - The name of the project provided in the command line

### Using Variables in Templates

You can use variables in:

1. **Files** - Any occurrence of `${variable_name}` will be replaced with its value
2. **File names** - Files with names like `${pc_project_name}.h` will be renamed to match your project name
3. **Directory names** - Directories with variables in their names will also be renamed

### Example Template with Variables

Here's an example of a CMake C++ template using variables:

```
sample-cmake-cpp/
├── CMakeLists.txt         # Contains: project(${pc_project_name} VERSION 0.0.1)
├── include/
│   └── ${pc_project_name}.h  # Will be renamed to your project name
└── src/
    └── main.cpp           # Contains: #include "${pc_project_name}.h"
```

When you create a project with:
```bash
./build/blueplate create awesome-project
```

The result will be:
```
awesome-project/
├── CMakeLists.txt         # Contains: project(awesome-project VERSION 0.0.1)
├── include/
│   └── awesome-project.h  # Renamed file
└── src/
    └── main.cpp           # Contains: #include "awesome-project.h"
```


## Creating a sample config

Use these commands to manage your configuration:

```bash
# Create a sample configuration with templates
./build/blueplate config create

# Remove existing configuration
./build/blueplate config remove
```
