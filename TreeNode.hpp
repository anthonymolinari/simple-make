#ifndef _TreeNode_hpp
#define _TreeNode_hpp

#include<iostream>
#include<string>
#include <vector>
#include "Token.hpp"
#include "GraphNode.hpp"

class TreeNode {
public:
    TreeNode( GraphNode *nNode );
    TreeNode *left();                // getter
    void left( TreeNode *leftPtr );  // setter
    TreeNode *right();
    void right( TreeNode *rightPtr );
    void print();   // print the value of this node
    GraphNode *graphNode();

private:
    GraphNode *makeNode;
    TreeNode *leftSubtree, *rightSubtree;

};

#endif
