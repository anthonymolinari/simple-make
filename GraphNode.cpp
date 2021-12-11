//
// Created by anthony on 11/2/21.
//
#include "GraphNode.hpp"
//
GraphNode::GraphNode(std::string name): _name(name), _onPath(false), _isATarget(false), _wasMade(false) {
    _listOfDependentNodes = new std::vector<GraphNode*>();
}

std::string GraphNode::getName() {
    return _name;
}

void GraphNode::setName(std::string name) {
    _name = name;
}

std::string GraphNode::getCommand() {
    return _command;
}

void GraphNode::setCommand(std::string cmnd) {
    _command = cmnd;
}

int GraphNode::getTimestamp() {
    return _timestamp;
}

void GraphNode::setTimestamp(long ts) {
    _timestamp = ts;
}

std::vector<GraphNode*>* GraphNode::dependentNodes() {
    return _listOfDependentNodes;
}

void GraphNode::runCommand() {
    if (this->isATarget())
        executeCommand( _command.c_str());
}

void GraphNode::addDependentNode(GraphNode *child) {
    _listOfDependentNodes->push_back(child);
}

bool GraphNode::onPath() {
    return _onPath;
}

void GraphNode::onPath(bool v) {
    _onPath = v;
}

bool GraphNode::wasMade() {
    return _wasMade;
}

void GraphNode::wasMade(bool v) {
    _wasMade = v;
}

bool GraphNode::isATarget() {
    return _isATarget;
}

void GraphNode::isATarget(bool v) {
    _isATarget = v;
}

int GraphNode::numDependentNodes() {
    return _listOfDependentNodes->size();
}

void GraphNode::print() {
    std::cout << _name << ": ";
    for (auto node : *_listOfDependentNodes)
        std::cout << node->getName();
    std::cout << std::endl;
}







