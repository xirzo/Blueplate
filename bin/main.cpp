#include "app.h"

/*
 * TODO: add a way to insert project_name or other variables inside the text of
 * templates for instance: ${pc_project_name} should be replace in any place
 * with project_name variable content
 *
 * TODO: create a config directory on startup if not present
 */

int main(int argc, char **argv) {
    return pc::run_app(argc, argv);
}
