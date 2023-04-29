//
// Created by Arclight-V on 29.04.2023.
//

#ifndef COMPUTOR_V1_COMPUTOR_H
#define COMPUTOR_V1_COMPUTOR_H

#include <string>

class Computor {
public:
    virtual bool LexicalAnalyzer(const std::string& str) = 0;
    virtual ~Computor() = default;
};

#endif //COMPUTOR_V1_COMPUTOR_H