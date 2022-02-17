//
// Created by Anatashi on 17.02.2022.
//

#ifndef COMPUTOR_V1_NODE_H
#define COMPUTOR_V1_NODE_H

using node = std::unique_ptr<IExpressionNode>;

class Node : public IExpressionNode {
protected:
    node left_;
    node right_;
public:

    Node() = delete;
    Node(const Node& rhs) = delete;
    Node& operator=(const Node& rhs) = delete;
    virtual ~Node() = default

    Node(char value) { value_ = value; }

    void setLeftNode(node left) { left_ = std::move(left); }

    void setRightNode(node right) { right_ = std::move(right); }

};

#endif //COMPUTOR_V1_NODE_H
