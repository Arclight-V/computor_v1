//
// Created by Anatashi on 21.01.2022.
//
#include <iostream>
#include <vector>

#include "Computor_v1/Computor_v1.h"


int main() {

    std::vector<std::string> vec_invalid_values = {"hello",
                                     "",
                                     ".0",
                                     "5 * X^0.0. + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                     "5 * 0X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                     "5a * 0X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                     "5 * X^0 & 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                     "5 * X^0 + 4 * X^1 - 9.3 * X^2 == 1 * X^0",
                                     "0.0.05 * X^0 + 4 * X^1 - 9.3 * X^2 == 1 * X^0 ",
                                     "5 *-X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                     "5 * X^0.0. + 4 * X^1 - 9.3 * X^2 = *1 * X^0",
                                     "5 * X^0.0. + 4 * X^1 - 9.3 * X^2 = 1 * X^*",
                                    "5 * X^0.0. + 4 * X^1 - 9.3 * X^2 = 1 * ",
                                    "*5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                    "5 * X^-0 + 4 * X^-1 - 9.3 * X^2 = 1 * X^0",
                                    "5 * X^.0 + 4 * X^-1 - 9.3 * X^2 = 1 * X^0"
                                     };

    for (auto& elem : vec_invalid_values) {
        Computor_v1 computorV1(elem.c_str());
        try {
            computorV1.parse();
        } catch (std::string str) {
            if (elem != str) {
                std::cout << elem << " " << str << '\n';
            }
        }
    }
}
