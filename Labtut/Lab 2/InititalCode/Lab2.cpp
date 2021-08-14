// Bai3.cpp : Defines the entry point for the console application.
//
#include <cmath>
#include <windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <GL/GLU.h>
#include <string>
#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

#define PI 3.1415926
int		screenWidth = 600;
int		screenHeight= 300;
Mesh	Shape2;
Mesh	Shape3_1;
Mesh	Shape3_2;
Mesh	Shape3_3;
Mesh	Shape4;
Mesh	tetrahedron;
Mesh	cube;
Mesh	Cylinder;
Mesh	HalfCylinder1;
Mesh	HalfCylinder2;
Mesh	shape1_1;
Mesh	Cylinder1;
int		nChoice = 1;
float angle = 0;

void mySpecialFunction(int key,int x,int y){
	if (key == GLUT_KEY_LEFT)
		angle = angle + 5;
	else if (key == GLUT_KEY_RIGHT)
		angle = angle - 5;
	glutPostRedisplay;
}
void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(4, 0, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 4, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 4);
	glEnd();
}
void Latch(float R, float r, float len, float height) {
	float y = height / 2;
	GLfloat* X = new GLfloat[181];
	GLfloat* Z = new GLfloat[181];
	GLfloat* x = new GLfloat[181];
	GLfloat* z = new GLfloat[181];

	for (int i = 0; i < 181; i++) {
		X[i] = R * cos(i * PI / 180.0);
		Z[i] = R * sin(i * PI / 180.0);
		x[i] = r * cos(i * PI / 180.0);
		z[i] = r * sin(i * PI / 180.0);
	}

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 181; i++) {
		glVertex3f(x[i], y, z[i]);
		glVertex3f(X[i], y, Z[i]);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 181; i++) {
		glVertex3f(x[i], -y, z[i]);
		glVertex3f(X[i], -y, Z[i]);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 181; i++) {
		glVertex3f(X[i], y, Z[i]);
		glVertex3f(X[i], -y, Z[i]);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 181; i++) {
		glVertex3f(x[i], y, z[i]);
		glVertex3f(x[i], -y, z[i]);
	}
	glEnd();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 181; i++) {
		glVertex3f(x[i], y, z[i]);
		glVertex3f(x[i], y, len);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 181; i++) {
		glVertex3f(x[i], -y, z[i]);
		glVertex3f(x[i], -y, len);
	}
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x[0], y, z[0]);
	glVertex3f(X[0], y, Z[0]);
	glVertex3f(X[0], y, len);
	glVertex3f(x[0], y, len);

	glVertex3f(x[0], -y, z[0]);
	glVertex3f(X[0], -y, Z[0]);
	glVertex3f(X[0], -y, len);
	glVertex3f(x[0], -y, len);

	glVertex3f(x[180], y, z[180]);
	glVertex3f(X[180], y, Z[180]);
	glVertex3f(X[180], y, len);
	glVertex3f(x[180], y, len);

	glVertex3f(x[180], -y, z[180]);
	glVertex3f(X[180], -y, Z[180]);
	glVertex3f(X[180], -y, len);
	glVertex3f(x[180], -y, len);

	glVertex3f(X[180], -y, Z[180]);
	glVertex3f(X[180], y, Z[180]);
	glVertex3f(X[180], y, len);
	glVertex3f(X[180], -y, len);

	glVertex3f(X[0], -y, Z[0]);
	glVertex3f(X[0], y, Z[0]);
	glVertex3f(X[0], y, len);
	glVertex3f(X[0], -y, len);
	glEnd();
	glPopMatrix();

	delete[] X;
	delete[] Z;
	delete[] x;
	delete[] z;
}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glViewport(0, 0, screenWidth/2, screenHeight);
	glRotatef(angle, 0, 1, 0);
	drawAxis();
	glColor3f(0, 0, 0);
	if (nChoice == 1)
		tetrahedron.DrawWireframe();
	else if (nChoice == 2)
		Cylinder1.DrawWireframe();
	else if (nChoice == 3)
		shape1_1.DrawWireframe();
	else if (nChoice == 4) {
		Shape3_2.DrawWireframe();
		Shape3_3.DrawWireframe();
		Shape3_1.DrawWireframe();
	}
	glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);

	drawAxis();
	if(nChoice == 1)
		tetrahedron.DrawColor();
	else if(nChoice == 2)
		Cylinder1.DrawColor();
	else if (nChoice == 3)
		shape1_1.DrawColor();
	else if (nChoice == 4) {
		Shape3_2.DrawColor();
		Shape3_3.DrawColor();
		Shape3_1.DrawColor();
	}
	glFlush();
    glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int main(int argc, CHAR* argv[])
{
	cout << "1. Tetrahedron" << endl;
	cout << "2. Cylinder1" << endl;
	cout << "3. Shape1_1" << endl;
	cout << "4. Shape 2" << endl;
	cout << "Input the choice: " << endl;
	cin  >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Huynh Thi Truong Duy-MSSV:1710779"); // open the screen window
	Latch(2,1,2,2);
	tetrahedron.CreateTetrahedron();
	cube.CreateCube(1);
	Cylinder.CreateHalfCylinder1(36,2,2);
	Shape4.CreateShape4(1,3,5);
	Shape3_1.CreateShape3_1(3, 1, 0.7);
	Shape3_2.CreateShape3_2(3, 1, 0.7);
	Shape3_3.CreateShape3_3(3, 1, 0.7);
	Shape2.CreateShape2(3,1,0.7);
	shape1_1.CreateShape1_1(2, 1, 4);
	Cylinder1.CreateCylinder(36, 2, 3);
	glutSpecialFunc(mySpecialFunction);
	myInit();
    glutDisplayFunc(myDisplay);
	  
	glutMainLoop();
	return 0;
}

