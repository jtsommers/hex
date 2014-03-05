#ifndef __cmps109_asmt04__Hex__
#define __cmps109_asmt04__Hex__

#include "Graph.h"		// Graph
#include <iostream>		// cout
#include <vector>		// vector
#include <list>			// list
#include <random>       // default_random_engine
#include <chrono>       // chrono::system_clock

using namespace std;

// White = West/East, Black = North/South
enum Allegiance { Unowned, White, Black };

enum searchStatus { white, black, grey };

// Class for the Hex game. Contains the dimension, Graph data, and state data.
class Hex{
public:
	// Constructor: Builds board of a given size. Size should be odd.
	Hex (int size);
	
	// playerTurn: Gets input from player and processes their move as white.
	void playerTurn();
	
	// computerTurn: AI determines optimal location for black player.
	void computerTurn(int numSimulations = 256);
	
	// playRandom: Fills a game board with moves taken randomly.
	void playRandom();
    void playRandom(vector< vector<Allegiance> > & owners);
	
	// pathExists: checks if an uninterrupted path exists for the given color.
	bool pathExists(Allegiance color);
    bool pathExists(Allegiance color, const vector< vector<Allegiance> > & owners);
	
	// Output operator overload.
	friend ostream& operator<< (ostream &out, Hex &h);
	
private:
	int dim;
	Graph board;
	vector< vector<Allegiance> > tileOwner;
	
	// buildBoard: Builds adjacency for the game board.
	void buildBoard();
	
	// node: Converts a row/col pair to the node address used by graph.
	int node(int row, int col);
};

#endif /* defined(__cmps109_asmt04__Hex__) */
