/* 
	Draws a pretty scene.
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include "ezloader.h"

// Globals
GLint callListIndex[8];
static GLuint texNames[8];

void init(){
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

}

void display(){

}

void reshape(int w, int h){

}

void keyboard(unsigned char key, int x, int y){

}

void mouse(int button, int state, int x, int y){

}

int main(int argc, char* argv[]){
	texNames[0] = 1;
	return 0;
}