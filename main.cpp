#include <iostream>
#include <iomanip>

#include "Computor/Computor_v1.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "# " << std::setw(std::strlen("Example:")) << "Error: " << "missing equation\n";
        std::cerr << std::setw(std::strlen("Example:") + 2)
                  << "Example: " << "./computor_v1 \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"\n";
        exit(EXIT_FAILURE);
    }
    std::stringstream ss(argv[1]);
    Computor_v1 computorV1(std::move(ss));
    if (!computorV1.Analyzer()) {
        computorV1.PrintErrors();
    } else {

    }


    return EXIT_SUCCESS;
}
