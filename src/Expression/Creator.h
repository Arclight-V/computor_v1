//
// Created by Anatashi on 21.02.2022.
//

#ifndef COMPUTOR_V1_CREATOR_H
#define COMPUTOR_V1_CREATOR_H

#include "Expression/NumberNode.h"
#include "Expression/UnknownNode.h"
#include "Expression/OperatorNode.h"
#include "Expression/PolynomialExpressionTree.h"

class Creator {
public:
    using node_u = std::unique_ptr<Node>;
    using node_s = std::shared_ptr<Node>;
    using expression_tree = std::unique_ptr<ExpressionTree>;
    using polynomial_tree = std::unique_ptr<PolynomialExpressionTree>;

    Creator() = default;
    Creator(const Creator& rhs) = delete;
    Creator& operator=(const Creator& rhs) = delete;
    virtual ~Creator() = default;

    node_u getUniqueNode() const { return std::make_unique<Node>(); }
    node_u getUniqueOperatorNode() const { return std::make_unique<OperatorNode>(); }
    node_u createUniqueOperatorNode(char value) const { return std::make_unique<OperatorNode>(value); }
    node_u getUniqueNumberNodeInt() const {return std::make_unique<NumberNode<int>>(); }
    node_u createUniqueNumberNodeInt(int value) { return std::make_unique<NumberNode<int>>(value); }
    node_u getUniqueNumberNodeDouble() const {return std::make_unique<NumberNode<double>>(); }
    node_u createUniqueNumberNodeDouble(double value) { return std::make_unique<NumberNode<double>>(value); }
    node_u getUniqueUnknownNode() const { return std::make_unique<UnknownNode>(); }
    node_u createUniqueUnknowNode(char value) { return std::make_unique<UnknownNode>(value); }

    node_s getSharedNode() const { return std::make_shared<Node>(); }
    node_s getSharedOperatorNode() const { return std::make_shared<OperatorNode>(); }
    node_s createSharedOperatorNode(char value) const { return std::make_shared<OperatorNode>(value); }
    node_s getSharedNumberNodeInt() const {return std::make_shared<NumberNode<int>>(); }
    node_s createSharedNumberNodeInt(int value) { return std::make_shared<NumberNode<int>>(value); }
    node_s getSharedNumberNodeDouble() const {return std::make_shared<NumberNode<double>>(); }
    node_s createSharedNumberNodeDouble(double value) { return std::make_shared<NumberNode<double>>(value); }
    node_s getSharedUnknownNode() const { return std::make_shared<UnknownNode>(); }
    node_s createSharedUnknowNode(char value) { return std::make_shared<UnknownNode>(value); }


    expression_tree getUniquePlynomialExpressionTree() const { return std::make_unique<PolynomialExpressionTree>(); }
    polynomial_tree getUniquePolynomialTree() const { return std::make_unique<PolynomialExpressionTree>(); }

};

#endif //COMPUTOR_V1_CREATOR_H
