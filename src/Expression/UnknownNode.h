//
// Created by Sergey Sudnichnikov on 17.02.2022.
//

#ifndef COMPUTOR_V1_UNKNOWNNODE_H
#define COMPUTOR_V1_UNKNOWNNODE_H

#include <ostream>
#include "Expression/Node.h"

using namespace expression;

namespace {
    constexpr NodeType kTypeUnknown = NodeType::unknown;
}

class UnknownNode : public Node {
private:
    char value_;
    int pow_ = 0;
public:
    UnknownNode() : Node(kTypeUnknown) {}
    UnknownNode(const UnknownNode& rhs) = delete;
    UnknownNode& operator=(const UnknownNode& rhs) = delete;
    virtual ~UnknownNode() = default;

    UnknownNode(char value) : Node(kTypeUnknown), value_(value) {}

    char getValue() const { return value_; }
    void setPow(int pow) {pow_ = pow; }

    friend std::ostream &operator<<(std::ostream &os, const UnknownNode &node) {
        os << node.value_ << "^" << node.pow_;
        return os;
    }
};

#endif //COMPUTOR_V1_UNKNOWNNODE_H
