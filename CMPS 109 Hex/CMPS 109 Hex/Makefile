#	Matthew Balousek (mbalouse@ucsc.edu)
#	Jordan Sommers (jtsommer@ucsc.edu)
#	Prof. Pohl
#	CMPS 109
#	12 March 2014
#	Assignment 6: Hex++ w/ GUI
#	See README for comments.

# Pull in Operating System
OS = $(shell uname)
CPP		= g++
CFLAGS	= -g -std=c++11

DIR		= CMPS\ 109\ Hex
NAME	= cmps109_asmt06
CLASSES	= Hex.o Graph.o main.o

# Add flags based on OS
ifeq ($(OS),Linux)
	CFLAGS += -lGL -lglut
endif 
ifeq ($(OS),Darwin)
	CFLAGS += -framework glut -framework OpenGL
endif

# Default target builds main program from classes and main program file
all: ${CLASSES}
	${CPP}	-o ${NAME}	${CFLAGS} ${CLASSES}

# Target expansion, builds .o files from ${CLASSES}.cpp
${CLASSES}: %.o: %.cpp
	${CPP}	-c	${CFLAGS} $< -o $@

clean:
	rm -f *.o ${NAME}

# Target to sync local working copy to unix.ic
sync: clean
	rsync -r -v --exclude '.*' --exclude '*.sublime*' ../${DIR} ${REMOTE_USER}@unix.ic.ucsc.edu:~/