//
// Created by Arclight-V on 29.04.2023.
//

#include <iostream>
#include <iomanip>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "# " << std::setw(std::strlen("Example:")) << "Error: " << "missing equation\n";
        std::cerr << std::setw(std::strlen("Example:") + 2)
                    << "Example: " << "./computor_v1 \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"\n";
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}