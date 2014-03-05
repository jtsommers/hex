#	Matthew Balousek (mbalouse@ucsc.edu)
#	Jordan Sommers (jtsommer@ucsc.edu)
#	Prof. Pohl
#	CMPS 109
#	12 March 2014
#	Assignment 6: Hex++ w/ GUI
#	See README for comments.

CC		= g++
CFLAGS	= -g -std=c++11 -Wall -O0

cmps109_asmt04:	main.o	Graph.o	Hex.o
	${CC} -o cmps109_asmt03 ${CFLAGS} main.o Graph.o Hex.o
	
Graph.o: Graph.h Graph.cpp
	${CC} -c	${CFLAGS}	Graph.cpp

Hex.o: Hex.h Hex.cpp
	${CC} -c	${CFLAGS}	Hex.cpp
	
main.o:	Graph.h Hex.h main.cpp
	${CC} -c	${CFLAGS}	main.cpp