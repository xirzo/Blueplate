#include "app.h"

/*
 * TODO: add a way to insert project_name or other variables inside the text of
 * templates for instance: ${pc_project_name} should be replace in any place
 * with project_name variable content
 *
 * TODO: --force option for config create
 * TODO: --force option for create
 *
 *
 *
 * FIX: unhandled exeptions when no config present
 * archlinux% blueplate create config
 * terminate called after throwing an instance of
 * 'std::filesystem::__cxx11::filesystem_error' what():  filesystem error:
 * directory iterator cannot open directory: No such file or directory
 * [/home/xirzo/.config/blueplate/templates] zsh: IOT instruction (core dumped)
 * blueplate create config archlinux% blueplate create app terminate called
 * after throwing an instance of 'std::filesystem::__cxx11::filesystem_error'
 *   what():  filesystem error: directory iterator cannot open directory: No
 * such file or directory [/home/xirzo/.config/blueplate/templates]
 */

int main(int argc, char **argv) {
    return pc::run_app(argc, argv);
}
