#include "project_creator.h"
#include <iostream>

namespace pc {

void create_project(
    const std::string &project_name,
    const std::string &template_name
) {
    std::cout << "Creating \"project_name\" with template \"" << template_name
              << "\"" << std::endl;
}

}  // namespace pc
