//
// Created by Sergey Sudnichnikov on 17.02.2022.
//

#ifndef COMPUTOR_V1_OPERATORNODE_H
#define COMPUTOR_V1_OPERATORNODE_H

#include "Expression/Node.h"

class OperatorNode : private Node  {
private:
    char value_;
public:
    OperatorNode() = delete;
    OperatorNode(const OperatorNode& rhs) = delete;
    OperatorNode& operator=(const OperatorNode& rhs) = delete;
    virtual ~OperatorNode() = default;

    OperatorNode(char value) : value_(value) {}

    char getOperator() const { return value_; }
};

#endif //COMPUTOR_V1_OPERATORNODE_H
