#include "Graph.h"

// Constructor: Builds a graph.
Graph::Graph (int size) {
	if (size <= 0) {
		size = 1;
	}
	setSize(size);
}

// setSize: Sets the number of nodes in the graph.
// NOTE: does not remove out-of-range edges from remaining graph.
void Graph::setSize (int newSize) {
	graphData.resize(newSize);
}

// getSize: Returns the number of nodes in the graph.
int Graph::getSize () {
	return int(graphData.size());
}

// edgeExists: returns true if the edge exists.
bool Graph::edgeExists(int source, int dest){
	for (int& i : graphData[source].adjacentNodes) {
		if (i == dest){
			return true;
		}
	}
	return false;
}

// setAdj: Sets adjacency from the source to dest, and opt'nally vice versa.
void Graph::addAdj(int source, int dest, bool mirror){
	if (edgeExists(source, dest)) {
		return;
	}
	graphData[source].adjacentNodes.push_back(dest);
	if (mirror) {
		graphData[dest].adjacentNodes.push_back(source);
	}
	
}

// getAdj: Returns the list of nodes adjacent to the requested node.
vector<int> Graph::getAdj(int node){
	return graphData[node].adjacentNodes;
}