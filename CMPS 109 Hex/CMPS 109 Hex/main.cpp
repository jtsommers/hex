//	Matthew Balousek (mbalouse@ucsc.edu)
//	Jordan Sommers (jtsommer@ucsc.edu)
//	Prof. Pohl
//	CMPS 109
//	12 March 2014
//	Assignment 6: Hex++ w/ GUI
//	See README for comments.

#include <iostream>		// cout, cin
#include <vector>		// vector
#include "Graph.h"		// Graph
#include "Hex.h"		// Hex

using namespace std;

void takeTurn(Hex& board, int turnMarker) {
    if (turnMarker % 2 == 0) {
        cout << board;
        // Plays out the rest of the board randomly if human enters "random"
        if (!board.playerTurn()) {
            board.playRandom();
        }
    } else {
        // Take AI turn
        board.computerTurn();
    }
}

bool checkPath(Hex& board) {
    if (board.pathExists(White)) {
        cout << board;
        cout << "\nWhite (-, East/West) wins! Hooray for humans!\n";
        return true;
    } else if (board.pathExists(Black)) {
        cout << board;
        cout << "\nBlack (O, North/South) wins! Hooray for computers!\n";
        return true;
    }
    return false;
}

int main(int argc, const char * argv[]){
    int boardSize = 11;
    Hex h(boardSize);
	
	for (int i = 0; i < boardSize * boardSize; i++) {
		takeTurn(h, i);
		if (checkPath(h)) {
            break;
        }
	}
		
    return 0;
}