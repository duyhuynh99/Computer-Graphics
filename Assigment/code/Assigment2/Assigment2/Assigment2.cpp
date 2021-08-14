#include <math.h>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <GL/GLU.h>
#include <string>

using namespace std;

#define PI			3.1415926
#define	COLORNUM		14
#define DEG2RAD	(PI / 180.0)


float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };


/// <summary>
/// Class
/// </summary>

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	string printPoint3()
	{
		string res = to_string(x) + " ; " + to_string(y) + " ; " + to_string(z);
		return res;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}
	void set(Color3& c)
	{
		r = c.r; g = c.g; b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}

};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw() {
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
private:
	float 	x, y;
};
class IntRect
{
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw() {
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int  getWidth() { return (r - l); }
	int  getHeight() { return (t - b); }
private:
	int	l, r, b, t;
};


class RealRect
{
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	float  getWidth() { return (r - l); }
	float  getHeight() { return (t - b); }
	void draw() {
		glRectf(l, b, r, t);
		glFlush();
	};// draw this rectangle using OpenGL
private:
	float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	void flip()
	{
		x = -x; y = -y; z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x * x + y * y + z * z);
	x = x / temp;
	y = y / temp;
	z = z / temp;
}

class VertexID
{
public:
	int		vertIndex; //index of this vertex in the vertex list
	int		normIndex; // index of this vertex's normal
	int		colorIndex; // index of this vertex's color
};

class Face
{
public:
	int	nVerts;
	VertexID* vert;
	// danh sách các đỉnh + vector pháp tuyến của đỉnh
	Vector3 vtNewell;
	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};


class Mesh
{
public:
	int	numVerts; // chiều dài
	Point3* pt; // danh sách các đỉnh

	int	numFaces; // chiều dài 
	Face* face; // danh sách các mặt

public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void Draw(int chooseColor);
	void DrawColor();
	void DrawColor2D();
	void SetColor(int colorIdx);
	void addMaterial(float ambient[], float diffuse[], float specular[], float shiness);

	void CreateHalfCylinder(int nSegment, float fHeight, float fRadius);
	void CreateHalfhalfCylinder(int nSegment, float fHeight, float fRadius);
	void CreateRectangular(float fLength, float fWidth, float fHeight);
	void vectorNewell();
};

void Mesh::CreateHalfCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = PI / (nSegment - 1);
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * -sin(fAngle * i);
		z = fRadius * -cos(fAngle * i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}
void Mesh::CreateHalfhalfCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = (PI ) / (nSegment - 1);
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * -sin(fAngle * i);
		z = fRadius * -cos(fAngle * i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}
void Mesh::CreateRectangular(float fLength, float fWidth, float fHeight)
{
	numVerts = 8;
	numFaces = 6;
	pt = new Point3[numVerts];
	face = new Face[numFaces];
	int idx = 0;
	int indexColor = 1;
	{
		pt[0].set(0, 0, 0); //A
		pt[1].set(0, 0, fLength); //B
		pt[2].set(fWidth, 0, fLength); //C
		pt[3].set(fWidth, 0, 0); //D
		pt[4].set(0, fHeight, 0); //A'
		pt[5].set(0, fHeight, fLength); //B
		pt[6].set(fWidth, fHeight, fLength); //C
		pt[7].set(fWidth, fHeight, 0); //D

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 2;
		face[idx].vert[3].vertIndex = 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 4;
		face[idx].vert[1].vertIndex = 5;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 7;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 1;
		face[idx].vert[1].vertIndex = 2;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 5;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 2;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 6;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 5;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;
	}
}
void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int ic = face[f].vert[v].colorIndex;
			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
			glNormal3f(face[f].vtNewell.x, face[f].vtNewell.y, face[f].vtNewell.z);
		}
		glEnd();
	}
}

void Mesh::DrawColor2D()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			ic = 2;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}


void Mesh::Draw(int chooseColor)
{
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
			glNormal3f(face[f].vtNewell.x, face[f].vtNewell.y, face[f].vtNewell.z);
		}
		glEnd();
	}
}

void Mesh::addMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void Mesh::SetColor(int colorIdx)
{
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::vectorNewell()
{
	for (int f = 0; f < numFaces; f++)
	{
		//float mx = 0, my = 0, mz = 0;
		float vectorN[] = { 0,0,0 };
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			vectorN[0] += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			vectorN[1] += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			vectorN[2] += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].vtNewell.set(vectorN[0], vectorN[1], vectorN[2]);
		face[f].vtNewell.normalize();
	}
}



int		screenWidth = 1200;
int		screenHeight = 600;
Mesh cylinder;
Mesh rectangular;
Mesh rectangular1;
Mesh halfcylinder;
Mesh halfhalfcylinder;
int		nChoice = 3;
float b = 0;
float a = 3;
float t = 1;
float dox = 0;
float doy = 0;
float doz = 0;
float camera_dis = 4.5;
float camera_height = 2;
float camera[3];
float cameraState[7];
bool lightState = true;
GLfloat camera_angle = 30.0;

GLfloat	fHalfSize = 8;
GLfloat fConstFS = fHalfSize;

void OnKeyboard(unsigned char key, int x, int y);
void OnKeySpecial(int key, int x, int y);
void updatePosCamera();

float* vectorNewell(float iVector[10][3], int n)
{
	float vectorResult[] = { 0,0,0 };
	for (int i = 0; i < n; i++)
	{
		vectorResult[0] += (iVector[i][1] - iVector[(i + 1) % n][1]) * (iVector[i][2] + iVector[(i + 1) % n][2]);
		vectorResult[1] += (iVector[i][2] - iVector[(i + 1) % n][2]) * (iVector[i][0] + iVector[(i + 1) % n][0]);
		vectorResult[2] += (iVector[i][0] - iVector[(i + 1) % n][0]) * (iVector[i][1] + iVector[(i + 1) % n][1]);
	}
	return vectorResult;
}

void rotateCamera(int value)
{
	camera_angle += (GLfloat)value;
	if (camera_angle > 360) camera_angle = camera_angle - 360.0f;
	camera[0] = camera_dis * cos(DEG2RAD * camera_angle);
	camera[2] = camera_dis * sin(DEG2RAD * camera_angle);
	glutTimerFunc(10, rotateCamera, 1);
	glutPostRedisplay();
}
void drawviengachvuong(float x, float y, float z, float alpha)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x , y, z);
	glVertex3f(x +2,y,z);
	glVertex3f(x+2 ,y,z+2);
	glVertex3f(x,y,z+2);
	glEnd();
}

void drawNen(float alpha)
{
	float x = -31.4;
	float z = -30;
	float y = 0;
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < 30; i++)
	{
		 x = x + 2.1;
		for (int j = 0; j < 30; j++) {
			 z = z + 2.1;
			drawviengachvuong(x, y, z, alpha);
		}
		z = -30;
	}
	glEnable(GL_LIGHTING);
}
void Drawshape1()
{
	glPushMatrix();
	glTranslatef(0, a, 0);
	glRotatef(doz, 0, 0, 1);
	glRotatef(doy, 0, 1, 0);
	glRotatef(dox,1,0,0);
	glScalef(t, t, t);
	glTranslatef(-1, 0, -6); // di chuyen goc toa do
	if (nChoice == 1)
	{
		rectangular.DrawWireframe();
	}

	else if (nChoice == 2)
	{
		rectangular.DrawColor2D();
	}
	else if (nChoice == 3)
	{
		rectangular.DrawColor();
		GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat shininess = 40.0;
		rectangular.addMaterial(ambient, diffuse, specular, shininess);
	}
	glTranslatef(3, 0, 7.5); // tra lai goc toa do ban dau

	// He so cua vat the

	glPopMatrix();
}
void Drawshape2()
{
	glPushMatrix();
	glTranslatef(0, a, 0);
	glRotatef(doz, 0, 0, 1);
	glRotatef(doy, 0, 1, 0);
	glRotatef(dox, 1, 0, 0);
	glScalef(t, t, t);
	glTranslatef(-1, 0, 0); // di chuyen goc toa do
	glRotatef(-90, 0, 1, 0);
	if (nChoice == 1)
	{
		rectangular1.DrawWireframe();
	}
	else if (nChoice == 2)
	{
		rectangular1.DrawColor2D();
	}
	else if (nChoice == 3)
	{
		rectangular1.DrawColor();
		GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat shininess = 40.0;
		rectangular1.addMaterial(ambient, diffuse, specular, shininess);
	}
	glTranslatef(3, 0, 7.5); // tra lai goc toa do ban dau

	glPopMatrix();
}
void Drawshape3()
{
	glPushMatrix();
	glTranslatef(0, a, 0);
	glRotatef(doz, 0, 0, 1);
	glRotatef(doy, 0, 1, 0);
	glRotatef(dox, 1, 0, 0);
	glScalef(t, t, t);
	glTranslatef(0, 0.5, -6); // di chuyen goc toa do
	glRotatef(-90,0,1,0);
	if (nChoice == 1)
	{
		halfcylinder.DrawWireframe();
	}
	else if (nChoice == 2)
	{
		halfcylinder.DrawColor2D();
	}
	else if (nChoice == 3)
	{
		halfcylinder.DrawColor();
		GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat shininess = 40.0;
		halfcylinder.addMaterial(ambient, diffuse, specular, shininess);
	}
	glPopMatrix();
}
void Drawshape4()
{
	glPushMatrix();
	glTranslatef(0, a, 0);
	glRotatef(doz, 0, 0, 1);
	glRotatef(doy, 0, 1, 0);
	glRotatef(dox, 1, 0, 0);
	glScalef(t, t, t);
	glTranslatef(-1, 0.5, 0); // di chuyen goc toa do
	glRotatef(145, 0, 1, 0);
	if (nChoice == 1)
	{
		halfhalfcylinder.DrawWireframe();
	}
	else if (nChoice == 2)
	{
		halfhalfcylinder.DrawColor2D();
	}
	else if(nChoice==3)
	{
		halfhalfcylinder.DrawColor();
		GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat shininess = 40.0;
		halfhalfcylinder.addMaterial(ambient, diffuse, specular, shininess);
	}
	glPopMatrix();
}


void DrawObject()
{
	glColor3f(0, 0, 0);
	Drawshape1();
	Drawshape2();
	Drawshape3();
	Drawshape4();

}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 15.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	if (lightState == true)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera[0], camera[1], camera[2], 0, 0, 0, 0, 1, 0);
	glViewport(0, 0, screenWidth, screenHeight);

	glClearStencil(0);
	glClearDepth(1.0f);

	DrawObject();

	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	drawNen(1);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();
	glScalef(1, -1, 1);
	DrawObject();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawNen(0.8f);
	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (nChoice != 3)
		return;
	else if (nChoice==3)
	{glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0); }

	glOrtho(-fHalfSize * 2, fHalfSize * 2, -fHalfSize / 2, fHalfSize + fHalfSize / 2, -1000, 1000);

}
void CreateObject()
{
	rectangular.CreateRectangular(6, 2, 1);
	rectangular.SetColor(0);
	rectangular.vectorNewell();

	rectangular1.CreateRectangular(4, 2, 1);
	rectangular1.SetColor(0);
	rectangular1.vectorNewell();

	halfcylinder.CreateHalfCylinder(36, 1, 1);
	halfcylinder.SetColor(0);
	halfcylinder.vectorNewell();

	halfhalfcylinder.CreateHalfhalfCylinder(36, 1, 2);
	halfhalfcylinder.SetColor(0);
	halfhalfcylinder.vectorNewell();

}
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Huynh Thi Truong Duy - MSSV: 1710779"); // open the screen window

	cout << "1     :  Che do hien thi khung day" << endl;
	cout << "2          :  Che do hien thi to mau 2D" << endl;
	cout << "3          :  Che do hien thi to mau 3D" << endl;
	cout << "U, u  :  Di chuyen len tren" << endl;
	cout << "D, d  :  Di chuyen xuong duoi" << endl;
	cout << "I, i  :  Phong to" << endl;
	cout << "O, o  :  Thu nho" << endl;
	cout << "X, x  :  Xoay quanh truc X" << endl;
	cout << "Y, y  :  Xoay quanh truc Y" << endl;
	cout << "Z, z  :  Xoay quanh truc Z" << endl;
	cout << "+   : Tang khoang cach camera" << endl;
	cout << "-   : Giam khoang cach camera" << endl;
	cout << "up arrow  : Tang chieu cao camera" << endl;
	cout << "down arrow: Giam chieu cao camera" << endl;
	cout << "<-        : Quay camera theo chieu kim dong ho" << endl;
	cout << "->        : Quay camera nguoc chieu kim dong ho" << endl;

	camera[0] = camera_dis * cos(DEG2RAD * camera_angle);
	camera[1] = camera_height;
	camera[2] = camera_dis * sin(DEG2RAD * camera_angle);
	cameraState[6] = 0;
	lightState = true;

	CreateObject();

	glutKeyboardFunc(OnKeyboard);
	glutSpecialFunc(OnKeySpecial);

	myInit();

	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
void updatePosCamera()
{
	camera[0] = camera_dis * cos(DEG2RAD * camera_angle);
	camera[1] = camera[1];
	camera[2] = camera_dis * sin(DEG2RAD * camera_angle);
}
void OnKeySpecial(int key, int x, int y)
{
	if (cameraState[6] == 1)
	{
		return;
	}
	switch (key)
	{
	case GLUT_KEY_LEFT:
	{
		camera_angle++;
		if (camera_angle > 360) camera_angle = camera_angle - 360.0f;
		updatePosCamera();
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		camera_angle--;
		if (camera_angle < 0) camera_angle = 360.0f;
		updatePosCamera();
		break;
	}
	case GLUT_KEY_UP:
	{
		if (fHalfSize >= fConstFS / 2 && camera[1] < 0)
		{
			fHalfSize -= 0.1;
			camera[1] += 0.1;
		}
		else
		{
			fHalfSize += 0.1;
			camera[1] += 0.1;
		}

		myInit();
		break;
	}
	case GLUT_KEY_DOWN:
	{
		if (fHalfSize >= fConstFS / 2 && camera[1] >= 0)
		{
			fHalfSize -= 0.1;
			camera[1] -= 0.1;
		}
		else
		{
			fHalfSize += 0.1;
			camera[1] -= 0.1;
		}

		myInit();
		break;
	}
	default:
		break;
	}
	glutPostRedisplay();
}
void OnKeyboard(unsigned char key, int x, int y)
{
	//cout << key << endl;
	if (key == '1')
	{
		nChoice = 1;
	}
	else if (key == '2')
	{
		nChoice = 2;
	}
	else if (key == '3')
	{
		nChoice = 3;
	}
	else if (key == 'd' || key == 'D')
	{
		if (a <= 0.4) return;
		else
		{
			a = a - 0.2;
		}
	}
	else if (key == 'u' || key == 'U')
	{
		if (a >= 6) return;
		else
		{
			a = a + 0.2;
		}
	}
	else if (key == 'x' || key == 'X')
	{
		dox = dox + 1;
	}
	else if (key == 'y' || key == 'Y')
	{
		doy = doy + 1;
	}
	else if (key == 'z' || key == 'Z')
	{
		doz = doz + 1;
	}
	else if (key == 'i' || key == 'I')
	{
		if (t >= 2.5)
			return;
		else
			t = t + 0.1;
	}
	else if (key == 'o' || key == 'O')
	{	
		if (t <= 1)
			return;
		else
			t = t - 0.1;
	}
	else if (key == '-' && cameraState[6] != 1)
	{
		if (camera_dis >= 0)
		{
			camera_dis += 0.1;
			fHalfSize += 0.1;
		}
		else
		{
			camera_dis += 0.1;
			fHalfSize -= 0.1;
		}
		updatePosCamera();
		//glOrtho(-fHalfSize * 2, fHalfSize * 2, -fHalfSize / 2, fHalfSize + fHalfSize / 2, -1000, 1000);
		myInit();
	}
	else if (key == '+' && cameraState[6] != 1)
	{
		if (camera_dis < 0)
		{
			camera_dis -= 0.1;
			fHalfSize += 0.1;
		}
		else
		{
			camera_dis -= 0.1;
			fHalfSize -= 0.1;
		}
		updatePosCamera();
		//glOrtho(-fHalfSize * 2, fHalfSize * 2, -fHalfSize / 2, fHalfSize + fHalfSize / 2, -1000, 1000);
		myInit();
	}
	glutPostRedisplay();
}
