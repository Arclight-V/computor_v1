//
// Created by Владимир on 29.04.2023.
//

#ifndef COMPUTOR_V1_COMPUTOR_V1_H
#define COMPUTOR_V1_COMPUTOR_V1_H

#include "Computor/Computor.h"

class Computor_v1 : public Computor {
public:
    Computor_v1() {};

    bool LexicalAnalyzer(const std::string &str) override;

};


#endif //COMPUTOR_V1_COMPUTOR_V1_H
