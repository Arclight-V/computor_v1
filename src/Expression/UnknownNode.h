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
    int pow_ = 1;
    double multipliable_ = 1;
public:
    UnknownNode() : Node(kTypeUnknown) {}
    UnknownNode(const UnknownNode& rhs) = delete;
    UnknownNode& operator=(const UnknownNode& rhs) = delete;
    virtual ~UnknownNode() = default;

    UnknownNode(char value) : Node(kTypeUnknown), value_(value) {}

    char getValue() const { return value_; }
    void setPow(int pow) {pow_ = pow; }
    void setMultipliabele(double number) { multipliable_ = number; }

    friend std::ostream &operator<<(std::ostream &os, const UnknownNode &node) {
        os << node.value_ << "^" << node.pow_;
        return os;
    }

    UnknownNode& operator*=(const UnknownNode& rhs) {
        pow_ += rhs.pow_;
        multipliable_ *= rhs.multipliable_;
        return *this;
    }

    UnknownNode& operator+=(const UnknownNode& rhs) {
        pow_ += rhs.pow_;
        multipliable_ *= rhs.multipliable_;
        return *this;
    }




    UnknownNode& operator*=(const NumberNode<double>& rhs) {
        multipliable_ += rhs.getValue();
        return *this;
    }

    UnknownNode& operator*=(const NumberNode<int>& rhs) {
        multipliable_ += rhs.getValue();
        return *this;
    }



};

#endif //COMPUTOR_V1_UNKNOWNNODE_H
