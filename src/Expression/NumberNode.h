//
// Created by Sergey Sudnichnikov on 17.02.2022.
//

#ifndef COMPUTOR_V1_NUMBERNODE_H
#define COMPUTOR_V1_NUMBERNODE_H

#include <ostream>
#include "Expression/Node.h"

using namespace expression;

namespace {
    constexpr NodeType kTypeNumber = NodeType::number;
}

// template class for handling int and double. Attention there is no template restriction
template <typename T>
class NumberNode : public Node {
private:
    T value_;
public:
    NumberNode() : Node(kTypeNumber) {} ;
    NumberNode(const NumberNode& rhs) = delete;
    NumberNode& operator=(const NumberNode& rhs) = delete;
    virtual ~NumberNode() = default;

    NumberNode(T value) : Node(kTypeNumber),  value_(value) {}

    T getValue() const { return value_; }
    void setValue(T value) { value_ = value; }

    friend std::ostream &operator<<(std::ostream &os, const NumberNode &node) {
        os << node.value_;
        return os;
    }

    T operator+(NumberNode<T>& rhs);
    NumberNode<T>& operator+=(NumberNode<T>& rhs);

};

template<typename T>
T NumberNode<T>::operator+(NumberNode<T> &rhs) {
    return value_ + rhs.getValue();;
}

template<typename T>
NumberNode<T>& NumberNode<T>::operator+=(NumberNode<T> &rhs) {
    value_ += rhs.getValue();
    return *this;
}


//// Relational Operators
template <typename T>
bool operator==(const NumberNode<T>& lhs, const NumberNode<T>& rhs) { return lhs.getValue() == rhs.getValue(); }

template <typename T>
bool operator!=(const NumberNode<T>& lhs, const NumberNode<T>& rhs) { return lhs.getValue() != rhs.getValue(); }

template <typename T>
bool operator<(const NumberNode<T>& lhs, const NumberNode<T>& rhs) { return lhs.getValue() < rhs.getValue(); }

template <typename T>
bool operator<=(const NumberNode<T>& lhs, const NumberNode<T>& rhs) { return lhs.getValue() <= rhs.getValue(); }

template <typename T>
bool operator>(const NumberNode<T>& lhs, const NumberNode<T>& rhs) { return lhs.getValue() > rhs.getValue(); }

template <typename T>
bool operator>=(const NumberNode<T>& lhs, const NumberNode<T>& rhs) { return lhs.getValue() >= rhs.getValue(); }



#endif //COMPUTOR_V1_NUMBERNODE_H
