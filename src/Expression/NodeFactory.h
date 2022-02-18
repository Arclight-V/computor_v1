//
// Created by Anatashi on 18.02.2022.
//

#ifndef COMPUTOR_V1_NODEFACTORY_H
#define COMPUTOR_V1_NODEFACTORY_H

#include "Expression/OperatorNode.h"
#include "UnknownNode.h"
#include "NumberNode.h"

using node = std::unique_ptr<Node>;
using expression::NodeType;

class NodeFactory {
public:
    static node CreateNode(NodeType type) {
        switch (type) {
            case NodeType::oper:
                return std::make_unique<OperatorNode>(type);
                break;
            case NodeType::unknown:
                return std::make_unique<UnknownNode>(type);
                break;
            case NodeType::number:
                return std::make_unique<NumberNode<int>>(type);
                break;
            default:
                break;
        }
    }
};

#endif //COMPUTOR_V1_NODEFACTORY_H
