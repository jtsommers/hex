OS = $(shell uname)
CC = g++ -std=c++11
FLAGS = -Wall -Wextra -Wno-deprecated -Wno-sign-compare

ifeq ($(OS),Linux)
	FLAGS += -lGL -lglut
endif 
ifeq ($(OS),Darwin)
	FLAGS += -framework glut -framework OpenGL
endif
all:
	echo $(shell uname)
	$(CC) $(FLAGS) glut_test.cpp -o test
	./test