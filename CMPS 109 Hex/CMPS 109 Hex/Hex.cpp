#include "Hex.h"
#include <algorithm>
#include <string>

// Constructor: Builds board of a given size. Size should be odd.
Hex::Hex(int size) : board(size*size), dim(size){
	vector<Allegiance> foo(size, Unowned);
	tileOwner.resize(size, foo);
	buildBoard();
}

// Output operator overload.
ostream& operator<< (ostream &out, Hex &h){
	// Print column header.
	out << "\n  ";
	for (int col = 0; col < h.dim; col++) {
		out << char('A' + col) << ' ';
		
	}
	out << endl;
	
	for (int row = 0; row < h.dim; row++) {
		for (int indent = 0; indent < row - 1; indent++) {
			out << " ";
		}
		if (row < 9 && row > 0) {
			out << ' ';
		}
		out << row + 1 << "\\ ";
		
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
		for (int col = 0; col < dim; col++) {
			int current = node(row, col);
			// Everything except the first column has a left node.
			if (col > 0) {
				// Push horizontal left
				board.addAdj(current, current - 1);
				// Push off-axis left
				if (row < dim - 1) {
					board.addAdj(current, node(row + 1, col - 1));
				}
			}
			// Everything except the last column has a right node.
			if (col < dim - 1) {
				// Push horizontal right
				board.addAdj(current, current + 1);
				if (row > 0) {
					board.addAdj(current, node(row - 1, col + 1));
				}
			}
			// Add column axis
			if (row > 0) {
				board.addAdj(current, current - dim);
			}
			if (row < dim - 1) {
				board.addAdj(current, current + dim);
			}
		}
	}
}

// node: Converts a row/col pair to the node address used by graph.
int Hex::node(int row, int col){
	return row * dim + col;
}

// playerTurn: Gets input from player and processes their move as white.
bool Hex::playerTurn(){
	cout << "\nPlayer's turn. (-, Red, East/West)" << endl;
	string playerChoice;
	bool inputIsBad;
	int choiceCol, choiceRow;
	
	do {
		cout << "Input a location: ";
		playerChoice = "";
		cin >> playerChoice;
		
        if (playerChoice.compare("random") == 0) {
            return false;
        }
        
		try {
			choiceCol = int(playerChoice[0] - 'A');
			choiceRow = stoi(playerChoice.substr(1)) - 1;
			inputIsBad = choiceCol < 0
						 || choiceCol >= dim
						 || choiceRow < 0
						 || choiceRow >= dim;
		} catch (std::invalid_argument) {
			inputIsBad = true;
		}
		
		if (inputIsBad) {
			cout << "Unable to parse that move. Use the format [Col][Row], e.g. \"A1\"." << endl;
			continue;
		}
		
		inputIsBad = tileOwner[choiceRow][choiceCol] != Unowned;
		if(inputIsBad){
			cout << "That space is occupied, try another." << endl;
		}
	} while (inputIsBad);
	
	tileOwner[choiceRow][choiceCol] = White;
	
	return true;
}

// computerTurn: AI determines optimal location for black player.
void Hex::computerTurn(int numSimulations){
	cout << "\nComputer's turn. (O, Blue, North/South)\n";
	auto timeBegin = chrono::high_resolution_clock::now();
	
	vector<vector<Allegiance>> simState = tileOwner;
	list<int> unownedNodes;
	for (int i = 0; i < dim*dim; i++){
		if (simState[i / dim][i % dim] == Unowned) {
			unownedNodes.push_back(i);
		}
	}
	
	int bestNode = -1,
	bestScore = -1;
	while (!unownedNodes.empty()) {
		// For each possible move, evaluate its fitness as a potential move.
		int score = 0;
		for (int i = 0; i < numSimulations; i++) {
			simState = tileOwner;
			simState[unownedNodes.front() / dim][unownedNodes.front() % dim] = Black;
			playRandom(simState);
			if (pathExists(Black, simState)) {
				score++;
			}
		}
		
		if (score > bestScore) {
			bestScore = score;
			bestNode = unownedNodes.front();
		}
		unownedNodes.pop_front();
	}
	
	auto timeEnd = chrono::high_resolution_clock::now();
	auto deltaTime = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeBegin).count();
	
	tileOwner[bestNode / dim][bestNode % dim] = Black;
	cout << "Computer chooses " << char('A' + (bestNode % dim)) << bestNode / dim + 1 << "."
		 << " (" << bestScore << '/' << numSimulations << ")\n";
	cout << "Turn elapsed in a mere " << deltaTime * 1.0 / 1000 << " seconds.\n";
	
	return;
}

void Hex::playRandom() {
    this->playRandom(tileOwner);
}

// playRandom: Fills a game board with moves taken randomly.
void Hex::playRandom(vector< vector<Allegiance> > & owners){
	vector<int> moveOrder;
	// Populate moveOrder with the addresses of unowned nodes.
	for (int i = 0; i < dim*dim; i++){
		if (owners[i / dim][i % dim] == Unowned) {
			moveOrder.push_back(i);
		}
	}
	
	// Mix up the vector. This serves as the move order.
	// Shuffle usage from cplusplus.com documentation.
	unsigned seed = static_cast<unsigned>( chrono::system_clock::now().time_since_epoch().count() );
	shuffle(moveOrder.begin(), moveOrder.end(), default_random_engine(seed));
	
	// Alternate between who gets to take a move. White goes first.
	bool whiteToMove = true;
	for (int i = 0; i < moveOrder.size(); i++) {
		owners[moveOrder[i] / dim][moveOrder[i] % dim] = whiteToMove?White:Black;
		whiteToMove = !whiteToMove;
	}
}

vector<vector<Allegiance>> Hex::getOwners(){
	return tileOwner;
}

void Hex::getOwners(vector<vector<Allegiance>> & f){
	f = tileOwner;
}

bool Hex::pathExists(Allegiance color) {
    return this->pathExists(color, tileOwner);
}
				
// pathExists: checks if an uninterrupted path exists for the given color.
bool Hex::pathExists(Allegiance color, const vector< vector<Allegiance> > & owners){
	vector<searchStatus> foo(dim, white);
	vector< vector<searchStatus> > nodeState(dim, foo);
	list<int> queue;
	
	// Enqueue possible root nodes into the queue.
	for (int i = 0; i < dim; i++) {
		if (color == White && owners[i][0] == White) {
			queue.push_back(i * dim);
			nodeState[i][0] = grey;
		} else if (color == Black && owners[0][i] == Black){
			queue.push_back(i);
			nodeState[0][i] = grey;
		}
	}
	
	// While there are nodes in the queue...
	while (!queue.empty()) {
		// Examine first node in the queue
		int qRow = (*queue.begin()) / dim,
			qCol = (*queue.begin()) % dim;
		
		// Enqueue any undiscovered children nodes.
		vector<int> qChildren = board.getAdj(node(qRow, qCol));
		for (int i = 0; i < qChildren.size(); i++) {
			if (nodeState[qChildren[i] / dim][qChildren[i] % dim] == white
				&& owners[qChildren[i] / dim][qChildren[i] % dim] == color) {
				// If a node on the opposite side exists in the queue, a path exists.
				int qcCol = qChildren[i] % dim,
					qcRow = qChildren[i] / dim;
				if ((color == White && qcCol == dim - 1)
					|| (color == Black && qcRow == dim - 1)){
					return true;
				}
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