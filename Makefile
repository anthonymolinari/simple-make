make.x: Graph.o main.o Token.o MakeTree.o TreeNode.o systemInterface.o ReaderToTokenizer.o GraphNode.o
	g++ -std=c++17 Graph.o GraphNode.o main.o Token.o MakeTree.o TreeNode.o systemInterface.o ReaderToTokenizer.o -o make.x

Graph.o: Graph.cpp Graph.hpp MakeTree.hpp TreeNode.hpp Token.hpp GraphNode.hpp systemInterface.hpp ReaderToTokenizer.hpp
	g++ -std=c++17 Graph.cpp -o Graph.o -c

GraphNode.o: GraphNode.cpp GraphNode.hpp systemInterface.hpp
	g++ -std=c++17 GraphNode.cpp -o GraphNode.o -c

main.o: main.cpp Graph.hpp MakeTree.hpp TreeNode.hpp Token.hpp GraphNode.hpp systemInterface.hpp ReaderToTokenizer.hpp
	g++ -std=c++17 main.cpp -o main.o -c

MakeTree.o: MakeTree.cpp MakeTree.hpp TreeNode.hpp Token.hpp GraphNode.hpp systemInterface.hpp
	g++ -std=c++17 MakeTree.cpp -o MakeTree.o -c

ReaderToTokenizer.o: ReaderToTokenizer.cpp ReaderToTokenizer.hpp Token.hpp
	g++ -std=c++17 ReaderToTokenizer.cpp -o ReaderToTokenizer.o -c

systemInterface.o: systemInterface.cpp systemInterface.hpp
	g++ -std=c++17 systemInterface.cpp -o systemInterface.o -c

Token.o: Token.cpp Token.hpp
	g++ -std=c++17 Token.cpp -o Token.o -c

TreeNode.o: TreeNode.cpp TreeNode.hpp Token.hpp GraphNode.hpp systemInterface.hpp
	g++ -std=c++17 TreeNode.cpp -o TreeNode.o -c