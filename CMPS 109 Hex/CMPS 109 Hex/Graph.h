#ifndef __cmps109_asmt06__Graph__
#define __cmps109_asmt06__Graph__

#include <iostream>	// cout
#include <vector>	// vector

using namespace std;

// Graph is a container for all the nodes in a graph.
class Graph{
public:
	// Constructor: Builds a graph.
	Graph(int numNodes = 1);
	
	// setSize: Sets the number of nodes in the graph.
	// NOTE: does not remove out-of-range edges from remaining graph.
	void setSize(int newSize);
	
	// getSize: Returns the number of nodes in the graph.
	int getSize();
	
	// edgeExists: returns true if the edge exists.
	bool edgeExists(int source, int dest);
	
	// addAdj: Sets adjacency from the source to dest, and opt'nally vice versa.
	void addAdj(int source, int dest, bool mirror = true);
	
	// getAdj: Returns the list of nodes adjacent to the requested node.
	vector<int> getAdj(int node);
	
private:
	// Node includes node data, if any, and edge properties.
	struct Node {
		vector<int> adjacentNodes;
	};
	
	vector<Node> graphData;
};

#endif