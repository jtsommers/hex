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

// GLUT includes
#ifdef __linux
#include <GL/gl.h>
#include <GL/glut.h>
#elif __unix
#include <GL/gl.h>
#include <GL/glut.h>
#elif __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif

using namespace std;

Hex h;
int turnCounter = 0;
bool win = false;

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

#pragma mark GLUT stuff

const int RESOLUTIONX = 800;
const int RESOLUTIONY = 600;

struct color {
	float r;
	float g;
	float b;
	
	color(float x, float y, float z){
		r = x;
		g = y;
		b = z;
	}
};

const color player(1.0, 0.0, 0.0);
const color enemy(0.0, 0.0, 1.0);
const color neutral(0.7, 0.7, 0.7);

//The shape superclass
class Shape{
protected:
	float xLoc;
	float yLoc;
	float scaleFactor;
    virtual void specificDraw() const;
    
public:
	static vector<Shape *> drawList;
	Shape(float x, float y, float s);
	void draw() const;
	void addMove(float x, float y){xLoc += x; yLoc += y;};
	void scale(float s){scaleFactor = s;};
};

vector<Shape*> Shape::drawList = vector<Shape*>();


//Shape constructor
Shape::Shape(float x, float y, float s):
xLoc(0),yLoc(0),scaleFactor(1){
	this->xLoc = x;
	this->yLoc = y;
	this->scaleFactor = s;
}

//Shape Draw:
void Shape::draw() const{
    glPushMatrix();
    glTranslatef(xLoc,yLoc,0);
    glScalef(scaleFactor,scaleFactor,1);
    
    this->specificDraw();
    glPopMatrix();
};

//Shape Specific Draw:
void Shape::specificDraw() const{
	cout << "Virtual specific draw\n";
}

class Hexagon : public Shape {
public:
	Hexagon(float x, float y, float s, float r, float g, float b);
	void changeColor(float r, float g, float b);
protected:
	float r;
	float g;
	float b;
	void specificDraw() const;
};

Hexagon::Hexagon(float x, float y, float s, float r, float g, float b): Shape(x, y, s) {
	this->r = r;
	this->g = g;
	this->b = b;
}

void Hexagon::changeColor(float r, float g, float b){
	this->r = r;
	this->g = g;
	this->b = b;
}

void Hexagon::specificDraw() const {
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glVertex2f(0.5, 0);
	glVertex2f(1, 0.25);
	glVertex2f(1, 0.75);
	glVertex2f(0.5, 1);
	glVertex2f(0, 0.75);
	glVertex2f(0, 0.25);
	glEnd();
}


//Main draw callback:
void drawStuff(){
	
    
	//Standard initialisation stuff:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	//Viewpoint:
	//Left, right, bottom, top, near, far
	glOrtho(0, RESOLUTIONX, RESOLUTIONY, 0, -2.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
    
	for(vector<Shape *>::iterator it = Shape::drawList.begin();
        it != Shape::drawList.end(); ++it){
		(*it)->draw();
	}
    
	glPushMatrix();
	glTranslatef(0,0,1);
	glPopMatrix();
	// glScalef(0.5,0.5,0.5);
	// glutSolidTeapot(15);
    
	glutSwapBuffers();
}



static void idle(){
    if (!win) {
        takeTurn(h, turnCounter);
        turnCounter++;
        if (checkPath(h)) {
            win = true;
        }
    }
	glutPostRedisplay();
	// glFlush();
}


void setupDrawList(){
    
	
	float scale = 40;
	float xOffset = 0.0;
	float xPadding = 1;
	float yPadding = -9;
	float yBase = RESOLUTIONY/2 - (30*13 + 10)/2;
    
	for(int j = 0; j < 13; j++){
		for(int i = 0; i < 13; i++){
			if ((i == 0 && j == 12) || (i == 0 && j == 0) || (i == 12 && j == 12) || (i == 12 && j == 0)) {
				// Black out corners
			} else if(i == 0 || i == 12) {
				//draw row of red for player
				Shape::drawList.push_back(new Hexagon(i * scale + xOffset + i * xPadding,
													  yBase + j * scale + j * yPadding,
													  scale,
													  player.r, player.g, player.b));
			} else if (j == 0 || j == 12){
				//draw row of blue for AI
				Shape::drawList.push_back(new Hexagon(i * scale + xOffset + i * xPadding,
													  yBase + j * scale + j * yPadding,
													  scale,
													  enemy.r, enemy.g, enemy.b));
			} else {
				// draw our vanilla shapes
				Shape::drawList.push_back(new Hexagon(i * scale + xOffset + i * xPadding,
													  yBase + j * scale + j * yPadding,
													  scale,
													  neutral.r, neutral.g, neutral.b));
			}
		}
		xOffset += (scale / 2);
	}
    
}

void initializeGLUT(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(RESOLUTIONX, RESOLUTIONY); //Set the size you want
	glutCreateWindow("GL Primer"); //Window name
    
	// glutKeyboardFunc(key);
	glutDisplayFunc(drawStuff); //Callback for the current window
	glutIdleFunc(idle);
	glutMainLoop();
}

int main(int argc, char **argv){
    int boardSize = 11;
    h = Hex(boardSize);
    turnCounter = 0;
    setupDrawList();
    
    //If there is a display, do something.
	if(getenv("DISPLAY")){
		std::string display (getenv("DISPLAY"));
		std::cout << display << std::endl;
        
		initializeGLUT(argc, argv);
		
	}else{ //otherwise complain
		std::cout <<"arg no display" << std::endl;
		// DISPLAY doesn't exist locally?
		if (__APPLE__) {
			initializeGLUT(argc, argv);
		}
	}
	
//	for (int i = 0; i < boardSize * boardSize; i++) {
//		takeTurn(h, i);
//		if (checkPath(h)) {
//            break;
//        }
//	}
//		
    return 0;
}