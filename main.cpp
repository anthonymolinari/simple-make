#include <iostream>
#include <cstdlib>
#include "Graph.hpp"

int main(int argc, const char *argv[] ) 
{
    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " name-of-a-makefile\n";
        exit(1);
    }

    // creates a Reader and build the dependency graph using the tokens that it returns.
    Graph *make = new Graph(argv[1]);
    make->parseDepGraph();
    if( make->isCyclic() )  {
        std::cerr << "Input graph has cycles.\n";
        exit(1);
    }
    make->runMake();

    return 0;
}
