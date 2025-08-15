# Blueplate

Blueplate is a small cross‑platform TUI helper to scaffold a new project from one of your local templates. It was tested on **Windows 10** (using *MinGW 15.1.0*) and **Linux**.

<p align="center">
  <img src="https://github.com/user-attachments/assets/2ce07732-9be7-4ddf-9f03-481f81a3c4d7" alt="blueplate" width="100%" />
</p>

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
## Variables & Configuration Guide


### What Are Template Variables?

Variables are placeholders you write inside your template files, file names, or directory names.  
At project creation time they are replaced with concrete values.

Syntax:  
```
${variable_name}
```

Example:
```
Project: ${pc_project_name}
Author:  ${pc_author}
```

After running:
```
blueplate create my-awesome-app
```
It becomes:
```
Project: my-awesome-app
Author: yourname 
```


Examples:

| Template Form | Becomes |
|---------------|---------|
| `include/${pc_project_name}.h` | `include/my-awesome-app.h` |
| `src/${pc_project_name}/main.cpp` | `src/my-awesome-app/main.cpp` |
| Content line: `#include "${pc_project_name}.h"` | `#include "my-awesome-app.h"` |

---

### Built‑In Variables

| Name | Meaning |
|------|---------|
| `pc_project_name` | The name you pass to `blueplate create <name>` |


### Custom Variables

Custom variables are defined inside the configuration file:
```
configuration.toml
```
located in your configuration directory:

| Platform | Base Config Path |
|----------|------------------|
| Linux (XDG) | `$XDG_CONFIG_HOME/blueplate` |
| Linux (fallback) | `$HOME/.config/blueplate` |
| macOS | `$HOME/Library/Application Support/blueplate` |
| Windows | `%APPDATA%\blueplate` |

Inside that directory:  
```
configuration.toml
templates/
```

Blueplate expects an array of 2‑element arrays under `[variables]` → `custom`:

```toml
[variables]
custom = [
    ["pc_version", "0.0.1"],
    ["pc_author", "xirzo"],
    ["pc_cmake_version", "3.24.1"]
]
```

Each inner array = `[ "key", "value" ]`.

These become usable variables:
```
${pc_version}
${pc_author}
${pc_cmake_version}
```

---
### Getting a sample config

Generate a starter configuration + sample template:

```bash
blueplate config create
```

This creates:
```
configuration.toml
templates/sample-cmake-cpp/...
```

In order to easily remove your config use:

```bash
blueplate config remove
```
