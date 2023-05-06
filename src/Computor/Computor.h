//
// Created by Arclight-V on 29.04.2023.
//

#ifndef COMPUTOR_V1_COMPUTOR_H
#define COMPUTOR_V1_COMPUTOR_H

#include <string>
#include <sstream>

class Computor {
public:
    virtual bool Analyzer() = 0;
    virtual void PrintErrors() = 0;
    virtual ~Computor() = default;
private:
    virtual bool LexicalAnalyzer(const std::string& str) = 0;
    virtual bool SyntaxAnalyzer(const std::string& str) = 0;
};

#endif //COMPUTOR_V1_COMPUTOR_H
