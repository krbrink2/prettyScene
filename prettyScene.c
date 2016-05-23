/* 
	Draws a pretty scene.
*/
#include <stdlib.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include "ezloader.h"

// Globals
GLint callListIndices[8];
static GLuint texNames[8];
GLfloat angle;
GLfloat elevation;
GLfloat distance;

void init(){
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(.2, .2, .2, 0);
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// Try messing with this
	texNames[0] = SOIL_load_OGL_texture("..//textures//wood.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	texNames[1] = SOIL_load_OGL_texture("..//textures//metal.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	texNames[2] = SOIL_load_OGL_texture("..//textures//paper.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Generate mesh call lists
	char teapotfname[] = "..//meshes//teapot.obj";
	char tablefname[] = "..//meshes//dtable.obj";
	char lampfname[] = "..//meshes//dlamp.obj";
	char toyplanefname[] = "..//meshes//toyplane.obj";
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

	distance = 20;
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(distance*sin(angle), elevation, distance*cos(angle), 0, 0, 0, 0, 1, 0);
	glEnable(GL_LIGHTING);

	// Lights
	GLfloat lightAmb[] = {.5*255/255, .5*229/255, .5*180/255};
	GLfloat lightDiff[] = {(float)255/255, (float)229/255, (float)180/255};
	GLfloat lightSpec[] = {1.0, 1.0, 1.0};
	//GLfloat light0Pos[] = {10*sin(angle/30), 10*cos(angle/30), 10};
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	GLfloat light0Pos[] = {-10.0, 10.0, -10.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec);
	GLfloat light1Pos[] = {10.0, 10.0, -10.0, 1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
	glEnable(GL_LIGHT1);

	// Teapot

	// Lamp

	// Toyplane

	// Table
	// Set material
	GLfloat matAmb[] = {.2, .2, .2, 1.f};
	GLfloat matDiff[] = {.6, .6, .6, 1.f};
	GLfloat matSpec[] = {1.f, 1.f, 1.f, 1.f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	// Texturing
	glActiveTexture(GL_TEXTURE0);
	//glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texNames[0]);
	// DO NOT let OpenGL generate texture vertices
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);*/
	glPushMatrix();
		glScalef(.1, .1, .1);
		glTranslatef(0, 1, 0);
		glCallList(callListIndices[1]);
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
	glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, w/h, .01, 100);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			elevation += 1;
			break;
		case 'a':
			angle += .1;
			break;
		case 's':
			elevation += -1;
			break;
		case 'd':
			angle += -.1;
			break;
		case 'z':
			distance += 1;
			break;
		case 'x':
			distance += -1;
			break;
		case 27:
			//exit(0);
			glutLeaveMainLoop();
			break;
	}
}

void mouse(int button, int state, int x, int y){

}

int main(int argc, char* argv[]){
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}