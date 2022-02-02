//
// Created by Anatashi on 21.01.2022.
//
#include <iostream>
#include <vector>

#include "Computor_v1/Computor_v1.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"


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
                                    "5 * X^.0 + 4 * X^-1 - 9.3 * X^2 = 1 * X^0",
                                    "5 * X^5^005 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                     };
    std::vector<std::string> vec_values;
    vec_values.reserve(vec_invalid_values.size());

    std::cout << "Invalid values test" << "\n";
    for (size_t i = 0; i < vec_invalid_values.size(); ++i) {
        Computor_v1 computorV1(vec_invalid_values[i].c_str());
        try {
            computorV1.parse();
        } catch (std::string str) {
            vec_values[i] = str;
        }
        std::cout << "Test " << i << " ";
        if (vec_invalid_values[i] != vec_values[i]) {
            std::cout << RED << "FAILURE" << '\n';
            std::cout << vec_invalid_values[i] << GREEN " " << vec_values[i] << '\n' << NORMAL;
        } else {
            std::cout << GREEN << "OK" << '\n' << NORMAL;
        }
    }

}
