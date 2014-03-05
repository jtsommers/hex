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

int main(int argc, const char * argv[]){
	int boardSize = 11;
	Hex h(boardSize);
	
	for (int i = 0; i < boardSize * boardSize; i++) {
		if(i%2 == 0){
			cout << h;
			if (!h.playerTurn()) {
                h.playRandom();
            }
		} else {
			h.computerTurn();
		}
		if (h.pathExists(White)) {
			cout << h;
			cout << "\nWhite (-, East/West) wins! Hooray for humans!\n";
			break;
		} else if(h.pathExists(Black)){
			cout << h;
			cout << "\nBlack (O, North/South) wins! Hooray for computers!\n";
			break;
		}
	}
		
    return 0;
}