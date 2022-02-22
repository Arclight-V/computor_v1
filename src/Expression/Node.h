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
    Node& operator=(const Node& rhs) = delete;
    virtual ~Node() = default;

    void setLeftNode(node left) { left_ = std::move(left); }
    void setRightNode(node right) { right_ = std::move(right); }

    NodeType getNodeType() const { return type_; }

};

#endif //COMPUTOR_V1_NODE_H
