#include "Hex.h"
#include <algorithm>

// Constructor: Builds board of a given size. Size should be odd.
Hex::Hex(int size) : board(size*size), dim(size){
	vector<Allegiance> foo(size, Unowned);
	tileOwner.resize(size, foo);
	buildBoard();
}

// Output operator overload.
ostream& operator<< (ostream &out, Hex &h){
	for (int row = 0; row < h.dim; row++) {
		for (int indent = 0; indent < row; indent++) {
			out << " ";
		}
		
		for (int col = 0; col < h.dim; col++) {
			switch (h.tileOwner[row][col]) {
				case White:
					out << "-";
					break;
				case Black:
					out << "O";
					break;
				default:
					out << ".";
					break;
			}
			out << " ";
		}
		out << '\n';
	}
	return out;
}

// buildBoard: Builds adjacency for the game board.
void Hex::buildBoard(){
	for (int row = 0; row < dim; row++) {
		for (int col = row; col < dim; col++) {
			// Check left...
			if (col - 1 >= 0) {
				board.addAdj(node(row, col), node(row, col - 1), true);
				// ...and bottom-left edges.
				if (row + 1 < dim) {
					board.addAdj(node(row, col), node(row + 1, col - 1), true);
				}
			}
			// Check top-left edge.
			if (row - 1 >= 0) {
				board.addAdj(node(row, col), node(row - 1, col), true);
			}
			// Check bottom-right edge.
			if (row + 1 < dim) {
				board.addAdj(node(row, col), node(row + 1, col), true);
			}
			// Check right...
			if (col + 1 < dim) {
				board.addAdj(node(row, col), node(row, col + 1), true);
				// ...and top-right edges.
				if (row - 1 >= 0) {
					board.addAdj(node(row, col), node(row - 1, col + 1), true);
				}
			}
		}
	}
}

// node: Converts a row/col pair to the node address used by graph.
int Hex::node(int row, int col){
	return row * dim + col;
}

// playRandom: Fills board with random moves taken by alternating sides.
void Hex::playRandom(){
	// Create a vector of ints with the values 0, 1, ..., (numNodes - 1).
	vector<int> moveOrder;
	for (int i = 0; i < dim*dim; i++){
		moveOrder.push_back(i);
	}
	
	// Mix up the vector. This serves as the move order.
	// Shuffle usage from cplusplus.com documentation.
	unsigned seed = static_cast<unsigned>( chrono::system_clock::now().time_since_epoch().count() );
	shuffle(moveOrder.begin(), moveOrder.end(), default_random_engine(seed));
	
	// Alternate between who gets to take a move. White goes first.
	bool whiteToMove = true;
	for (int i = 0; i < moveOrder.size(); i++) {
		tileOwner[moveOrder[i] / dim][moveOrder[i] % dim] = whiteToMove?White:Black;
		whiteToMove = !whiteToMove;
	}
}
				
// pathExists: checks if an uninterrupted path exists for the given color.
bool Hex::pathExists(Allegiance color){
	vector<searchStatus> foo(dim, white);
	vector< vector<searchStatus> > nodeState(dim, foo);
	list<int> queue;
	
	// Enqueue possible root nodes into the queue.
	for (int i = 0; i < dim; i++) {
		if (color == White && tileOwner[i][0] == White) {
			queue.push_back(i * dim);
			nodeState[i][0] = grey;
		} else if (color == Black && tileOwner[0][i] == Black){
			queue.push_back(i);
			nodeState[0][i] = grey;
		}
	}
	
	// While there are nodes in the queue...
	while (!queue.empty()) {
		// Examine first node in the queue
		int qRow = (*queue.begin()) / dim,
			qCol = (*queue.begin()) % dim;
		
		// If a node on the opposite side exists in the queue, a path exists.
		if ((color == White && qCol == dim - 1)
			|| (color == Black && qRow == dim - 1)){
			return true;
		}
		
		// Enqueue any undiscovered children nodes.
		vector<int> qChildren = board.getAdj(node(qRow, qCol));
		for (int i = 0; i < qChildren.size(); i++) {
			if (nodeState[qChildren[i] / dim][qChildren[i] % dim] == white
				&& tileOwner[qChildren[i] / dim][qChildren[i] % dim] == color) {
				queue.push_back(qChildren[i]);
				nodeState[qChildren[i] / dim][qChildren[i] % dim] = grey;
			}
		}
		
		// Remove the front element.
		queue.pop_front();
		nodeState[qRow][qCol] = black;
	}
	
	// A path for this color does not exist.
	return false;
}