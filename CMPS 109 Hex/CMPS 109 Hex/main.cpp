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
	Hex h(11);
	h.playRandom();
	cout << h << endl;
	
	cout << (h.pathExists(Black)?"Black (O, North/South)":"White (-, East/West)")
		 << " wins!" << endl;
	
    return 0;
}