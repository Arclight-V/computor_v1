//
// Created by Arclight-V on 29.04.2023.
//

#ifndef COMPUTOR_V1_COMPUTOR_H
#define COMPUTOR_V1_COMPUTOR_H



class Computor {
public:
    virtual bool Analyzer() = 0;
    virtual void PrintErrors() = 0;
    virtual ~Computor() = default;
private:
    virtual bool LexicalAnalyzer() = 0;
    virtual bool SyntaxAnalyzer() = 0;
    virtual bool isArithmeticOperator(const char ch) = 0;
    virtual void print() = 0;
};

#endif //COMPUTOR_V1_COMPUTOR_H
