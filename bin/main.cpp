#include "app.h"

/*
 * TODO: add a way to insert project_name or other variables inside the text of
 * templates for instance: ${pc_project_name} should be replace in any place
 * with project_name variable content
 *
 * TODO: --force option for config create
 * TODO: --force option for create
 */

int main(int argc, char **argv) {
    return pc::run_app(argc, argv);
}
