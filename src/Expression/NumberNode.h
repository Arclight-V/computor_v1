//
// Created by Sergey Sudnichnikov on 17.02.2022.
//

#ifndef COMPUTOR_V1_NUMBERNODE_H
#define COMPUTOR_V1_NUMBERNODE_H

#include "Expression/Node.h"

using expression::NodeType;

// TODO Исправить шаблон
template<typename T>
using isIntOrDouble = typename std::enable_if<std::is_same<T, int>::value || std::is_same<T, double>::value, bool>;

//template<typename T>
//constexpr bool is_int_or_double_v = std::is_same<T, int>::value || std::is_same<T, double>::value;

// template class for handling int and double.
template <typename T, isIntOrDouble<T> = true>
class NumberNode : public Node {
private:
    T value_;
public:
    NumberNode() = delete;
    NumberNode(const NumberNode& rhs) = delete;
    NumberNode& operator=(const NumberNode& rhs) = delete;
    virtual ~NumberNode() = default;

    NumberNode(NodeType type) : Node(type) {}

    NumberNode(NodeType type,
               T value) : Node(type),  value_(value) {}

    T getValue() const { return value_; }
    void setValue(T value) { value_ = value; }
};

// Relational Operators
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
