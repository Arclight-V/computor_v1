//
// Created by Владимир on 29.04.2023.
//

#ifndef COMPUTOR_V1_COMPUTOR_H
#define COMPUTOR_V1_COMPUTOR_H

#include <string>

// Interface
class Computor {

public:
    virtual bool LexicalAnalyzer(const std::string &str) = 0;

};

#endif //COMPUTOR_V1_COMPUTOR_H
