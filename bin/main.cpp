#include <iostream>
#include "app.h"

// программа - консольное приложение, которое
// должно создавать новые проекты. готовые заготовки
// проектов должны лежать в своей папке конфиге

int main(int argc, char **argv) {
    if (int init_result = pc::init_app(argc, argv) != 0) {
        return init_result;
    }

    return 0;
}
