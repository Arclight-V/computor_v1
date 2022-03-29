//
// Created by Anatashi on 17.02.2022.
//

#ifndef COMPUTOR_V1_NODE_H
#define COMPUTOR_V1_NODE_H

#include <memory>
#include "Expression/IExpressionNode.h"

namespace expression {
    enum NodeType {
        base,
        oper,
        unknown,
        number
    };
}
using namespace expression;

class Node : public IExpressionNode {
    using node = std::unique_ptr<Node>;
private:
    node left_;
    node right_;
    const NodeType type_;

public:
    Node() : type_(NodeType::base) {}
    Node(NodeType type) : type_(type) {}
    Node(const Node& rhs) = delete;
    Node(Node&& rhs) = default;
    Node& operator=(const Node& rhs) = delete;
    virtual ~Node() = default;

    void setLeftNode(node left) { left_ = std::move(left); }
    void setRightNode(node right) { right_ = std::move(right); }
    node getLeftNode() { return std::move(left_); }
    node getRightNode() { return std::move(right_); }

    NodeType getNodeType() const { return type_; }

};

class StackNode {
    using node = std::unique_ptr<Node>;
private:
    node head_ = nullptr;
public:
    StackNode() = default;
    StackNode(const StackNode& rhs) = delete;
    StackNode(StackNode&& rhs) = default;
    StackNode& operator=(const StackNode& rhs) = delete;
    StackNode& operator=(StackNode&& rhs) = default;
    virtual ~StackNode() = default;

    void push(node u_ptr) {
        if (head_ == nullptr) {
            head_ = std::move(u_ptr);
        } else {
            u_ptr->setRightNode(std::move(head_));
            head_ = std::move(u_ptr);
        }
    };
    node pop() {
        node ret = std::move(head_);
        head_ = ret->getRightNode();
        return ret;
    };
};

#endif //COMPUTOR_V1_NODE_H
