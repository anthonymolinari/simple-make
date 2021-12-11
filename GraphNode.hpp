#ifndef _GraphNode_hpp
#define _GraphNode_hpp

#include<iostream>
#include<string>
#include<vector>

#include "systemInterface.hpp"

class GraphNode {
public:
    GraphNode( std::string name );
    std::string getName();
    void setName( std::string name );
    void setTimestamp(long ts);
    int getTimestamp();
    std::vector<GraphNode *> *dependentNodes();
    void setCommand(std::string cmnd);
    std::string getCommand();
    void runCommand();  // execute the command associated with this node. Only for target nodes.
    void addDependentNode(GraphNode *child);
    bool onPath();
    void onPath(bool v);
    bool wasMade();
    void wasMade(bool v);
    bool isATarget();
    void isATarget(bool v);
    int numDependentNodes();
    void print();

private:
    std::string _name, _command;
    long _timestamp;
    std::vector<GraphNode *> *_listOfDependentNodes;
    // _onPath: has this node been seen before
    bool _onPath, _isATarget, _wasMade;
};

#endif