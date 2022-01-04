#include <iostream>

#include "ParserArgv.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Error: argc must by 2\n";
        exit(EXIT_FAILURE);
    }

    ParserArgv parserArgv(argv[1]);

    try {
        parserArgv.parse();
    } catch (int return_value) {
        exit(return_value);
    }

    return EXIT_SUCCESS;
}
