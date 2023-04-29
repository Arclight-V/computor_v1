//
// Created by Arclight-V on 29.04.2023.
//

#include "Computor_v1.h"
#include <iostream>
bool Computor_v1::LexicalAnalyzer(const std::string &str) {
    for (size_t found = str.find_first_not_of(allow_chars);
        found != std::string::npos;
        found = str.find_first_not_of(allow_chars, found)) {
        //TODO: move to error_manager
        std::cout << "# " << str << "\n" <<  "is |" << str[found] << "| " << "position " << found << "\n";
        ++found;
    }

    return false;
}

