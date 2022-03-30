//
// Created by OUT-Kalanchin-VV on 12.03.2022.
//

#ifndef COMPUTOR_V1_EXPRESSIONTREE_H
#define COMPUTOR_V1_EXPRESSIONTREE_H

#include "Expression/Node.h"

class ExpressionTree {
    using node = std::unique_ptr<Node>;
protected:
    node tree_;
private:

    void push(node node_to_push) {
        if (tree_ == nullptr) {
            tree_ = std::move(node_to_push);
        } else {
            node_to_push->setRightNode(std::move(tree_));
            tree_ = std::move(node_to_push);
        }
    }

    node pop() {
        node p = std::move(tree_);
        tree_ = p->getRightNode();
        return p;
    }

public:
    ExpressionTree() = default;
    ExpressionTree(const ExpressionTree& rhs) = delete;
    ExpressionTree(ExpressionTree&& rhs) = default;
    ExpressionTree& operator=(const ExpressionTree& rhs) = delete;
    ExpressionTree& operator=(ExpressionTree&& rhs) = default;
    virtual ~ExpressionTree() = default;

    virtual void addNode(std::unique_ptr<Node> node) {
        if (node->getNodeType() == expression::oper) {
            node->setRightNode(pop());
            node->setLeftNode(pop());
            push(std::move(node));
        } else {
            push(std::move(node));
        }
    }

    virtual bool eval() {
        return true;
    }
};

#endif //COMPUTOR_V1_EXPRESSIONTREE_H
