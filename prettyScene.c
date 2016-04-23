/* 
	Draws a pretty scene.
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include "ezloader.h"

// Globals
GLint callListIndices[8];
static GLuint texNames[8];

void init(){
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(.2, .2, .2, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// Try messing with this
	texNames[0] = SOIL_load_OGL_texture("..//textures//wood.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	texNames[1] = SOIL_load_OGL_texture("..//textures//metal.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	texNames[2] = SOIL_load_OGL_texture("..//textures//paper.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Generate mesh call lists
	char teapotfname[] = "teapot.obj";
	char tablefname[] = "dtable.obj";
	char lampfname[] = "dlamp.obj";
	char toyplanefname[] = "toyplane.obj";
	callListIndices[0] = glGenLists(4);
	callListIndices[1] = callListIndices[0] + 1;
	callListIndices[2] = callListIndices[0] + 2;
	callListIndices[3] = callListIndices[0] + 3;
	// teapot
	FILE *fp = fopen(teapotfname, "r");
	if(!fp){
		printf("Failed to open file %s!\n", teapotfname);
		exit(1);
	}
	ezloadCallList(callListIndices[0], fp);
	fclose(fp);
	// table
	fp = fopen(tablefname, "r");
	if(!fp){
		printf("Failed to open file %s!\n", tablefname);
		exit(1);
	}
	ezloadCallList(callListIndices[1], fp);
	fclose(fp);
	// lamp
	fp = fopen(lampfname, "r");
	if(!fp){
		printf("Failed to open file %s!\n", lampfname);
		exit(1);
	}
	ezloadCallList(callListIndices[2], fp);
	fclose(fp);
	// toyplane
	fp = fopen(toyplanefname, "r");
	if(!fp){
		printf("Failed to open file %s!\n", toyplanefname);
		exit(1);
	}
	ezloadCallList(callListIndices[3], fp);
	fclose(fp);
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 1, 1, 0, 0, 0, 0, 1, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	
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