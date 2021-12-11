//
// Created by anthony on 11/2/21.
//

#include "MakeTree.hpp"

int MakeTree::size(TreeNode* root) {
    if (root == nullptr)
        return 0;

    return size(root->left()) + size(root->right()) + 1;
}

GraphNode* MakeTree::find(std::string name) {
    return find(name, _root);
}

GraphNode* MakeTree::find(std::string name, TreeNode *root) {
    if (root == nullptr)
        return nullptr;

    if (name > root->graphNode()->getName())
        return find(name, root->right());

    if (name < root->graphNode()->getName())
        return find(name, root->left());

    return root->graphNode();
}

void MakeTree::insert( GraphNode *nNode ) {
    if (find(nNode->getName()) == nullptr) {
        _root = insert(_root, nNode);
    }
}

TreeNode* MakeTree::insert(TreeNode *root, GraphNode *nNode) {
    if (root == nullptr)
        return new TreeNode(nNode);

    if (root->graphNode()->getName() < nNode->getName())
        root->right(insert(root->right(), nNode));
    else if (root->graphNode()->getName() > nNode->getName())
        root->left(insert(root->left(), nNode));

    return root;
}

void MakeTree::print(TreeNode* root) {
    // in order print
    if (root == nullptr)
        return;

    print(root->right());
    std::cout << root->graphNode()->getName() << std::endl;
    print(root->left());
}

