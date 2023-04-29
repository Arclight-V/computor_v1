//
// Created by Владимир on 29.04.2023.
//

#ifndef COMPUTOR_V1_COMPUTOR_V1_H
#define COMPUTOR_V1_COMPUTOR_V1_H

#include "Computor.h"

namespace {
    constexpr const char* allow_chars {"1234567890Xx*-+=^. "};
}

class Computor_v1 : public Computor {
public:
    Computor_v1() = default;

    virtual ~Computor_v1() = default;

    bool LexicalAnalyzer(const std::string &str) override;
};


#endif //COMPUTOR_V1_COMPUTOR_V1_H
