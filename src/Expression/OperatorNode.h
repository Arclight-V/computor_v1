//
// Created by Sergey Sudnichnikov on 17.02.2022.
//

#ifndef COMPUTOR_V1_OPERATORNODE_H
#define COMPUTOR_V1_OPERATORNODE_H

#include "Expression/Node.h"

using::expression::NodeType;

class OperatorNode : public Node  {
private:
    char value_;
public:
    OperatorNode() = delete;
    OperatorNode(const OperatorNode& rhs) = delete;
    OperatorNode& operator=(const OperatorNode& rhs) = delete;
    virtual ~OperatorNode() = default;

    OperatorNode(NodeType type) : Node(type) {};
    OperatorNode(NodeType type, char value) : Node(type),  value_(value) {};

    char getOperator() const { return value_; };
    void setOperator(char value) {value_ = value; };
};

#endif //COMPUTOR_V1_OPERATORNODE_H
