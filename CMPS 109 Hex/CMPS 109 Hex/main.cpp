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

//debug mode. 0 = random play, 1 = player input
const int MODE = 0;

int main(int argc, const char * argv[]){
	int boardSize = 11;
	Hex h(boardSize);
	
	if (MODE == 0) {
		h.playRandom();
		cout << h;
	} else if(MODE == 1){
		for (int i = 0; i < boardSize * boardSize; i++) {
			if(i%2 == 0){
				cout << h;
				h.playerTurn();
			} else {
				h.computerTurn();
			}
		}
	}
	
	cout << (h.pathExists(Black)?"Black (O, North/South)":"White (-, East/West)")
		 << " wins!" << endl;
	
    return 0;
}