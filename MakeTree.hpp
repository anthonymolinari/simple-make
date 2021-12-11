
#ifndef _MakeTree_hpp
#define _MakeTree_hpp

#include<iostream>
#include<string>

#include "TreeNode.hpp"

class MakeTree {
public:
    MakeTree(): _root(nullptr) {}

    void insert( GraphNode *nNode );

    GraphNode *find( std::string name );
    void print() { print(_root); }   // print the tree using in-order traversal
    TreeNode  *getRoot() { return _root; }

    int size() { return size(_root); }

private:
    TreeNode *_root;
    TreeNode *insert(TreeNode *tNode, GraphNode *nNode);
    GraphNode *find(std::string name, TreeNode* root);
    void print(TreeNode *root);
    int size(TreeNode *root);
};

#endif
