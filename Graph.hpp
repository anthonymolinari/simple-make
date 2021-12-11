
#ifndef _Graph_hpp
#define _Graph_hpp

#include<iostream>
#include<cstring>

#include <vector>
#include <stack>

#include "MakeTree.hpp"
#include "ReaderToTokenizer.hpp"
#include "Token.hpp"
#include "systemInterface.hpp"

class Graph {
public:
    Graph( std::string name );
    void print();
    void parseDepGraph();
    void runMake();
    bool isCyclic();

private:
    bool isCyclic(GraphNode *);
    void print(GraphNode *);
    void resetPath(GraphNode *);
    bool doLink(GraphNode *);
    void updateTimeStamps(GraphNode *);
    std::string _fileToMake, _targetToMake;
    GraphNode *firstTarget;
    MakeTree *_tree;  // MakeTree implements a binary-search tree similar to BinSearchTree
};

#endif
