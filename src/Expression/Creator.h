//
// Created by Anatashi on 21.02.2022.
//

#ifndef COMPUTOR_V1_CREATOR_H
#define COMPUTOR_V1_CREATOR_H

#include "Expression/NumberNode.h"
#include "Expression/UnknownNode.h"
#include "Expression/OperatorNode.h"

class Creator {
public:
    using node = std::unique_ptr<Node>;

    Creator() = default;
    Creator(const Creator& rhs) = delete;
    Creator& operator=(const Creator& rhs) = delete;
    virtual ~Creator() = default;

    node getNode() const { return std::make_unique<Node>(); }
    node getOperatorNode() const { return std::make_unique<OperatorNode>(); }
    node createOperatorNode(char value) const { return std::make_unique<OperatorNode>(value); }
    node getNumberNodeInt() const {return std::make_unique<NumberNode<int>>(); }
    node createNumberNodeInt(int value) { return std::make_unique<NumberNode<int>>(value); }
    node getNumberNodeDouble() const {return std::make_unique<NumberNode<double>>(); }
    node createNumberNodeDouble(double value) { return std::make_unique<NumberNode<double>>(value); }
    node getUnknownNode() const { return std::make_unique<UnknownNode>(); }
    node createUnknowNode(char value) { return std::make_unique<UnknownNode>(value); }

};

#endif //COMPUTOR_V1_CREATOR_H
