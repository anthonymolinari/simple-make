//
// Created by anthony on 11/2/21.
//

#ifndef _Graph_cpp
#define _Graph_cpp

#include "Graph.hpp"
#include "systemInterface.hpp"

Graph::Graph( std::string name ): _fileToMake(name), firstTarget(nullptr) {
    _tree = new MakeTree();
}

void Graph::print() {
    if ( firstTarget == nullptr )
        return;

    std::cout << firstTarget->getName() << std::endl;
    for (auto child : *firstTarget->dependentNodes()) {
        print(child);
    }
}

void Graph::print(GraphNode * node) {
    std::cout << node->getName() << std::endl;
    for (auto child : *node->dependentNodes()) {
        print(child);
    }
}



void Graph::parseDepGraph() {
    // fileToMake, colon, targets..., eol, tab, command (if no -c then is bin file, else object file)

    ReaderToTokenizer *tokenizer = new ReaderToTokenizer(_fileToMake);
    Token *token = new Token();
    GraphNode *targetNode;
    GraphNode *depNode;
    token = tokenizer->getToken();

    while (!token->eof()) {
        if (token->isTarget()) {
            // check if target is in makeTree
            targetNode = _tree->find(token->context());
            if (targetNode == nullptr) {
                targetNode = new GraphNode(token->context());
                this->_tree->insert(targetNode); // insert into BST -> targetNode
            }
            targetNode->isATarget(true); // flip target flag for this file
            if (firstTarget == nullptr)
                firstTarget = targetNode;
            // next token should be colon. if so, then throw out and move on
            if (tokenizer->getToken()->isColon()) {
                token = tokenizer->getToken();
                while(token->isDep()) {
                    // check if dep already exists in makeTree
                    depNode = _tree->find(token->context());
                    if (depNode == nullptr) {
                        // create new graphNode and insert into bst
                        depNode = new GraphNode(token->context());
                        _tree->insert(depNode);
                    }
                    targetNode->addDependentNode(depNode);
                    token = tokenizer->getToken();
                }
                // check and skip eol and tab
                if (token->eol() && tokenizer->getToken()->isTab()) {
                    token = tokenizer->getToken();
                    // next token should be the command
                    if (token->isCommand())
                        targetNode->setCommand(token->context());
                    else {
                        std::cout << "Expected command after target: dependencies. Found ";
                        token->print();
                        exit(5);
                    }
                }
                else {
                    std::cout << "Syntax error: missing newline/indent";
                    exit(5);
                }
            }
            else {
                std::cout << "Target not succeeded by a ':' ";
                exit(5);
            }
        }
        token = tokenizer->getToken();
    }
}

void Graph::runMake() {
    std::stack<GraphNode*> compileStack;

    // get timestamps of all nodes
    updateTimeStamps(firstTarget); // check age of binary


    // determine what needs to be compiled
    compileStack.push(firstTarget);
    for (auto dep : *firstTarget->dependentNodes()) {
        if (dep->isATarget()) {
            if (!dep->wasMade()) {
                compileStack.push(dep);
                dep->wasMade(true);
            }
            else {
                // check if target is older than dependencies
                for (auto child : *dep->dependentNodes()) {
                    if (child->getTimestamp() > dep->getTimestamp()) {
                        compileStack.push(dep);
                        break;
                    }
                }
            }
        }
    }

    // print but do not run compilation -- debug only
//    while(!compileStack.empty()) {
//        std::cout << "Compiling: " << compileStack.top()->getName() << std::endl;
//        std::cout << "\t" << compileStack.top()->getCommand() << std::endl;
//        compileStack.pop();
//    }

    // run compilation
    /// Todo: fix
    while(!compileStack.empty()) {
        // check if object files need to be linked
        if (compileStack.top() == firstTarget && !doLink(firstTarget)) { // does not work properly
            std::cout << "'" << firstTarget->getName() << "' is up to date." << std::endl;
            break;
        }
        if(!executeCommand(compileStack.top()->getCommand().c_str())) {
            std::cerr << "Could not compile: " << compileStack.top()->getName() << std::endl;
            exit(9);
        }
        updateTimeStamps(compileStack.top());
        compileStack.pop();
    }

}

bool Graph::doLink(GraphNode* target) {
    // compile only if dependencies are newer than target
    for (auto child : *target->dependentNodes())
        if (child->getTimestamp() > target->getTimestamp())
            return true;
    return false;
}

void Graph::updateTimeStamps(GraphNode * node) {
    long time;
    if (timestamp(node->getName().c_str(),&time)) {
        node->setTimestamp(time);
        if (node->isATarget() && time != -1)
            node->wasMade(true); // target file found had been made
    }
    else {
        std::cout << "Error: missing file from make recipe: " << node->getName();
        exit(5);
    }

    // call recursively for all dependant nodes
    for (auto child : *node->dependentNodes()) {
        updateTimeStamps(child);
    }
}

bool Graph::isCyclic() {
    // set onPath false for all GraphNodes.
//    resetPath(firstTarget);

    return isCyclic(firstTarget);
}

bool Graph::isCyclic(GraphNode* node) {
    if (node->onPath() && node->isATarget())
        return true; // node has been seen before, thus we have a cycle

    // else we have not seen this node, flip onPath
    node->onPath(true);

    // recursively call for all children
    for (auto child : *node->dependentNodes()) {
        return isCyclic(child);
    }

    return false;
}

void Graph::resetPath(GraphNode * node) {
    node->onPath(false);
    for (auto child : *node->dependentNodes()) {
        resetPath(child);
    }
}

#endif