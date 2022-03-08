//
// Created by Anatashi on 10.01.2022.
//

#include "tools/tools.h"

namespace tools {

    std::vector<std::string> ft_split(std::string str, std::string delimiter) {
        std::vector<std::string> vec;
        size_t pos = 0;

        while ((pos = str.find(delimiter)) != std::string::npos) {
            vec.push_back(str.substr(0, pos));
            str.erase(0, pos + delimiter.length());
        }

        vec.push_back(str);

        return vec;
    }
}