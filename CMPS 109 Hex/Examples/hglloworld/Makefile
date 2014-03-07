# Makefile for __ASSIGNMENT_NAME__ CMPS 109
# Builds __ASSIGNMENT_NAME__ program - __ASSIGNMENT_DESCRIPTION__
# Author: Jordan Sommers
# Email: jtsommer@ucsc.edu

CPP     = g++
CFLAGS	= -Wall -Wextra -std=c++11 -framework OpenGL -framework GLUT
# Project specific variables: containing directory and program name (same as .cpp file)
DIR		= hglloworld
NAME	= test

# Default target builds the program from source based on name variable set above
${NAME}:	${NAME}.o
	${CPP}  -o ${NAME}  ${CFLAGS} ${NAME}.o

# Target builds object from source
${NAME}.o:		${NAME}.cpp
	${CPP}  -c  ${CFLAGS} ${NAME}.cpp

# Target to clean all compiled object files and program file
clean: 
	rm -f ${NAME} *.o

# Target to sync local working copy to unix.ic
sync:
	rsync -r -v --exclude '.*' --exclude '*.sublime*' ../${DIR} jtsommer@unix.ic.ucsc.edu:~/