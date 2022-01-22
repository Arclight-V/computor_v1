#include <iostream>

#include "Computor_v1/Computor_v1.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Error: argc must by 2\n";
        exit(EXIT_FAILURE);
    }

    Computor_v1 Computor_v1(argv[1]);

    try {
        Computor_v1.parse();
    } catch (int return_value) {
        exit(return_value);
    }

    return EXIT_SUCCESS;
}
