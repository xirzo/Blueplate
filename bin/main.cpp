#include "app.h"

/*
 * TODO: add a way to insert project_name or other variables inside the text of
 * templates for instance: ${pc_project_name} should be replace in any place
 * with project_name variable content
 * .
 * Now I need to add read of the configuration.toml, sample_config creation with
 * it is already present
 *
 * TODO: --force option for config create
 * TODO: --force option for create
 *
 * TODO: create commands to add keys and save them into config
 *
 * TODO: remove ability to create names with "-" when using c++ or c
 *
 */

int main(int argc, char **argv) {
    return pc::run_app(argc, argv);
}
