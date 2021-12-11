//
// Created by anthony on 11/2/21.
//
#include "TreeNode.hpp"

// tree node implementations
TreeNode::TreeNode(GraphNode *nNode): makeNode(nNode),
                                      leftSubtree(nullptr),
                                      rightSubtree(nullptr) {}

TreeNode* TreeNode::left() {
    return leftSubtree;
}

void TreeNode::left(TreeNode *leftPtr) {
    leftSubtree = leftPtr;
}

TreeNode* TreeNode::right() {
    return rightSubtree;
}

void TreeNode::right(TreeNode *rightPtr) {
    rightSubtree = rightPtr;
}

void TreeNode::print() {
    std::cout << makeNode->getName() << std::endl;
}

GraphNode* TreeNode::graphNode() {
    return makeNode;
}