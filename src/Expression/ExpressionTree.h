//
// Created by OUT-Kalanchin-VV on 12.03.2022.
//

#ifndef COMPUTOR_V1_EXPRESSIONTREE_H
#define COMPUTOR_V1_EXPRESSIONTREE_H

#include "Expression/Node.h"
#include "Expression/NumberNode.h"
#include "Expression/UnknownNode.h"

class ExpressionTree {
    using node_s = std::shared_ptr<Node>;
protected:
    node_s tree_;
    node_s sum(node_s lhs, node_s rhs) {
        if (lhs->getNodeType() == expression::number &&
            rhs->getNodeType() == expression::number) {
            node_s ret = std::make_shared<NumberNode<double>>(
                    static_cast<NumberNode<double>*>(lhs.get())->getValue() +
                    static_cast<NumberNode<double>*>(rhs.get())->getValue());
            lhs = nullptr;
            rhs = nullptr;
            return ret;
        } else if ((lhs->getNodeType() == expression::unknown &&
                   rhs->getNodeType() == expression::unknown) &&
                ()
                (static_cast<UnknownNode*>(lhs.get())->getPow() ==
                static_cast<UnknownNode*>(rhs.get())->getPow())) {
            node_s ret = std::make_shared<>()
        }
        return nullptr;
    }
private:

    void push(node_s node_to_push) {
        if (tree_ == nullptr) {
            tree_ = std::move(node_to_push);
        } else {
            node_to_push->setRightNode(std::move(tree_));
            tree_ = std::move(node_to_push);
        }
    }

    node_s pop() {
        node_s p = std::move(tree_);
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

    virtual void addNode(node_s node) {
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
