#include <iostream>

#include "Computor_v1/Computor_v1.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Error: argc must by 2\n";
        exit(EXIT_FAILURE);
    }

    Computor_v1 Computor_v1(argv[1]);

    bool is_ok =  Computor_v1.parse();
    if (is_ok) {
        Computor_v1.PrintSolution();
    } else {
        Computor_v1.PrintError();
    }

    return EXIT_SUCCESS;
}
