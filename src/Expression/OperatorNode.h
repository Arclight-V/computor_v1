//
// Created by Sergey Sudnichnikov on 17.02.2022.
//

#ifndef COMPUTOR_V1_OPERATORNODE_H
#define COMPUTOR_V1_OPERATORNODE_H

#include <ostream>
#include "Expression/Node.h"

using namespace expression;

namespace {
    constexpr NodeType kTypeOper = NodeType::oper;
}

class OperatorNode : public Node  {
private:
    char value_;
public:
    OperatorNode() : Node(kTypeOper) {}
    OperatorNode(const OperatorNode& rhs) = delete;
    OperatorNode& operator=(const OperatorNode& rhs) = delete;
    virtual ~OperatorNode() = default;

    OperatorNode(char value) : Node(kTypeOper),  value_(value) {};

    char getOperator() const { return value_; };
    void setOperator(char value) {value_ = value; };

    friend std::ostream &operator<<(std::ostream &os, const OperatorNode &node) {
        os << node.value_;
        return os;
    }
};

#endif //COMPUTOR_V1_OPERATORNODE_H
