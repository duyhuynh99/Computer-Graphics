
#include "Mesh.h"
#include <math.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <GL/GLU.h>
#include <string>
#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};





void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius) {
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle =  PI / nSegment;
	float	x, y, z;

	pt[0].set(0, 4, fHeight/2);
	for (i = 0; i < nSegment; i++) {
		x = fRadius * cos(fAngle*i);
		y = fRadius * sin(fAngle*i)+4;
		z = fHeight / 2;
		pt[i + 1].set(x, y, z);

		z = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, 4, -fHeight/2);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++) {
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

	for (i = 0; i < nSegment; i++) {
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

	for (i = 0; i < nSegment; i++) {
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

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}
void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}
void Mesh::CreateShape4(float day,float rong, float cao) {
	int i;
	int idx = 0;
	numVerts = 16;
	pt = new Point3[numVerts];
	pt[0].set(0, cao, 0);
	pt[1].set(rong,cao,0);
	pt[2].set(rong,cao,day);
	pt[3].set(0,cao,day);
	pt[4].set(day, cao-day, day);
	pt[5].set(day, cao-day, 0);
	pt[6].set(rong-day, cao-day, 0);
	pt[7].set(rong-day, cao-day, day);
	pt[8].set(0, 0, day);
	pt[9].set(0, 0, 0);
	pt[10].set(day, 0, 0);
	pt[11].set(day, 0, day);
	pt[12].set(rong-day, 0, day);
	pt[13].set(rong-day, 0, 0);
	pt[14].set(rong, 0, 0);
	pt[15].set(rong, 0, day);
	numFaces = 14;
	face = new Face[numFaces];
//mặt trên
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 1;
	face[idx].vert[2].vertIndex = 2;
	face[idx].vert[3].vertIndex = 3;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//mặt dưới
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 8;
	face[idx].vert[1].vertIndex = 9;
	face[idx].vert[2].vertIndex = 10;
	face[idx].vert[3].vertIndex = 11;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 12;
	face[idx].vert[1].vertIndex = 13;
	face[idx].vert[2].vertIndex = 14;
	face[idx].vert[3].vertIndex = 15;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//mặt chữ u trong
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4;
	face[idx].vert[1].vertIndex = 5;
	face[idx].vert[2].vertIndex = 10;
	face[idx].vert[3].vertIndex = 11;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4;
	face[idx].vert[1].vertIndex = 5;
	face[idx].vert[2].vertIndex = 6;
	face[idx].vert[3].vertIndex = 7;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 6;
	face[idx].vert[1].vertIndex = 7;
	face[idx].vert[2].vertIndex = 12;
	face[idx].vert[3].vertIndex = 13;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//mat bentrong
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 1;
	face[idx].vert[2].vertIndex = 6;
	face[idx].vert[3].vertIndex = 5;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 5;
	face[idx].vert[2].vertIndex = 10;
	face[idx].vert[3].vertIndex = 9;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 1;
	face[idx].vert[1].vertIndex = 6;
	face[idx].vert[2].vertIndex = 13;
	face[idx].vert[3].vertIndex = 14;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//mat ben ngoai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 2;
	face[idx].vert[1].vertIndex = 3;
	face[idx].vert[2].vertIndex = 4;
	face[idx].vert[3].vertIndex = 7;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3;
	face[idx].vert[1].vertIndex = 4;
	face[idx].vert[2].vertIndex = 11;
	face[idx].vert[3].vertIndex = 8;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 2;
	face[idx].vert[1].vertIndex = 15;
	face[idx].vert[2].vertIndex = 12;
	face[idx].vert[3].vertIndex = 7;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//mặt bên
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 3;
	face[idx].vert[2].vertIndex = 8;
	face[idx].vert[3].vertIndex = 9;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 7;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 1;
	face[idx].vert[1].vertIndex = 2;
	face[idx].vert[2].vertIndex = 15;
	face[idx].vert[3].vertIndex = 14;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 7;
	idx++;
}
void Mesh::CreateShape2(float fLength, float fWidth, float fHeight)
{
	int nSegment = 36;
	int	idx = 0, idp = 0;
	float fAngle = PI / nSegment;
	float x, y, z;
	float fRadius = fWidth / 3.0;
	int iStart, iCount;
	numVerts = 8 + nSegment * 4;
	numFaces = 4 + 2 * nSegment;// 6 + nSegment * 4;
	face = new Face[numFaces];
	pt = new Point3[numVerts];
	//mat duoi
	{
		iStart = idp;
		float iStop;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius * -sin(fAngle * i);
			z = fRadius * -cos(fAngle * i);
			y = 0;
			//cout << x << ";" << y << ";" << z << endl;
			pt[iStart + i].set(x, y, z); // 17
			idp++;
		}
		iStart = idp;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius * sin(fAngle * i) + fLength;
			z = fRadius * cos(fAngle * i);
			y = 0;
			//cout << x << ";" << y << ";" << z << endl;
			pt[iStart + i].set(x, y, z); // 17
			idp++;
		}
		pt[idp].set(pt[0].x, pt[0].y, pt[0].z);
		idp++;
		//cout << "=================" << endl;
		iCount = idp;
		iStart = 0;
		face[idx].nVerts = iCount;
		face[idx].vert = new VertexID[face[idx].nVerts];
		for (int i = 0; i < iCount; i++)
		{
			face[idx].vert[i].vertIndex = iStart + i;
			//cout << pt[iStart+i].printPoint3() << endl;
		}
		//cout << "======= END ======" << endl;
		idx++;
	}
	//mat tren
	{
		iStart = idp;
		iCount = 0;
		float iStop;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius * -sin(fAngle * i);
			z = fRadius * -cos(fAngle * i);
			y = fHeight;
			pt[iStart + i].set(x, y, z); // 17
			idp++;
			iCount++;
		}
		int iStart2 = idp;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius * sin(fAngle * i) + fLength;
			z = fRadius * cos(fAngle * i);
			y = fHeight;

			pt[iStart2 + i].set(x, y, z);
			idp++;
			iCount++;
		}
		pt[idp].set(pt[iStart].x, pt[iStart].y, pt[iStart].z);
		idp++;
		iCount++;
		face[idx].nVerts = iCount;
		face[idx].vert = new VertexID[face[idx].nVerts];
		for (int i = 0; i < iCount; i++)
		{
			face[idx].vert[i].vertIndex = iStart + i;
		}
		idx++;
	}
	//xung quang
	{
		iStart = 0;
		int iStart2 = 2 * nSegment + 3;
		iCount = 2 * nSegment + 2;
		for (int i = 0; i < iCount; i++)
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + i;
			face[idx].vert[1].vertIndex = iStart2 + i;
			face[idx].vert[2].vertIndex = iStart2 + i + 1;
			face[idx].vert[3].vertIndex = iStart + i + 1;
			idx++;
		}
	}
}
void Mesh::CreateHalfCylinder1(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];
	int idp;
	int		i;
	int		idx;
	float	fAngle = PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * -sin(fAngle*i);
		z = fRadius * -cos(fAngle*i);
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
void Mesh::CreateHalfCylinder2(int nSegment, float fHeight, float fRadius, float length)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = PI / nSegment;
	float	x, y, z;

	pt[0].set(length, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * sin(fAngle*i) + length;
		z = fRadius * cos(fAngle*i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(length, -fHeight / 2, 0);

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
void Mesh::CreateShape3_1(float fLength, float fWidth, float fHeight)
{
	float linber = fWidth/6.0;
	float fRadius = fWidth / 3.0;
	float a = fLength/14.0;
	float b = (fLength*10) / 14.0;
	float phanc = (fLength)/15.0;
	int i;
	int idx = 0;
	numVerts = 24;
	pt = new Point3[numVerts];
	pt[0].set(0, fHeight/2.0, -fRadius);//A
	pt[1].set(a, fHeight / 2.0,-fRadius);//B
	pt[2].set(a, fHeight / 2.0, fRadius);//C
	pt[3].set(0, fHeight / 2.0, fRadius);//D
	pt[4].set(0, -fHeight / 2.0, -fRadius);//A'
	pt[5].set(a,- fHeight / 2.0, -fRadius);//B'
	pt[6].set(a, -fHeight / 2.0, fRadius);//C'
	pt[7].set(0, -fHeight / 2.0, fRadius);//D'
	pt[8].set(b, fHeight / 2.0, -fRadius);//E
	pt[9].set(fLength, fHeight / 2.0, -fRadius);//F
	pt[10].set(fLength, fHeight / 2.0, fRadius);//G
	pt[11].set(b, fHeight / 2.0, fRadius);//H
	pt[12].set(b,- fHeight / 2.0, -fRadius);//E'
	pt[13].set(fLength,- fHeight / 2.0, -fRadius);//F'
	pt[14].set(fLength, -fHeight / 2.0, fRadius);//G'
	pt[15].set(b, -fHeight / 2.0, fRadius);//H'
	pt[16].set(a, fHeight / 2.0, -linber);//K
	pt[17].set(b, fHeight / 2.0, -linber);//L
	pt[18].set(b, fHeight / 2.0, linber);//M
	pt[19].set(a, fHeight / 2.0, linber);//N
	pt[20].set(a,- fHeight / 2.0, -linber);//K'
	pt[21].set(b, -fHeight / 2.0, -linber);//L'
	pt[22].set(b, -fHeight / 2.0, linber);//M'
	pt[23].set(a, -fHeight / 2.0, linber);//N'
	numFaces = 14;
	face = new Face[numFaces];
//mặt trên
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 1;
	face[idx].vert[2].vertIndex = 2;
	face[idx].vert[3].vertIndex = 3;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 1;
	face[idx].vert[1].vertIndex = 8;
	face[idx].vert[2].vertIndex = 17;
	face[idx].vert[3].vertIndex = 16;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 19;
	face[idx].vert[1].vertIndex = 18;
	face[idx].vert[2].vertIndex = 11;
	face[idx].vert[3].vertIndex = 2;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 8;
	face[idx].vert[1].vertIndex = 9;
	face[idx].vert[2].vertIndex = 10;
	face[idx].vert[3].vertIndex =11;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//mặt dưới
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4;
	face[idx].vert[1].vertIndex = 5;
	face[idx].vert[2].vertIndex = 6;
	face[idx].vert[3].vertIndex = 7;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 5;
	face[idx].vert[1].vertIndex = 12;
	face[idx].vert[2].vertIndex = 21;
	face[idx].vert[3].vertIndex = 20;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 23;
	face[idx].vert[1].vertIndex = 22;
	face[idx].vert[2].vertIndex = 15;
	face[idx].vert[3].vertIndex = 6;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 12;
	face[idx].vert[1].vertIndex = 13;
	face[idx].vert[2].vertIndex = 14;
	face[idx].vert[3].vertIndex = 15;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//mặt xung quang
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 9;
	face[idx].vert[2].vertIndex = 13;
	face[idx].vert[3].vertIndex = 4;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3;
	face[idx].vert[1].vertIndex = 10;
	face[idx].vert[2].vertIndex = 14;
	face[idx].vert[3].vertIndex = 7;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//mặt trong
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 16;
	face[idx].vert[1].vertIndex = 17;
	face[idx].vert[2].vertIndex = 21;
	face[idx].vert[3].vertIndex = 20;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 18;
	face[idx].vert[1].vertIndex = 19;
	face[idx].vert[2].vertIndex = 23;
	face[idx].vert[3].vertIndex = 22;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 16;
	face[idx].vert[1].vertIndex = 19;
	face[idx].vert[2].vertIndex = 23;
	face[idx].vert[3].vertIndex = 20;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 17;
	face[idx].vert[1].vertIndex = 18;
	face[idx].vert[2].vertIndex = 22;
	face[idx].vert[3].vertIndex = 21;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
}
void Mesh::CreateShape3_2(float fLength, float fWidth, float fHeight)
{
	int nSegment = 36;
	int	idx = 0, idp = 0;
	float fAngle = PI / nSegment;
	float x, y, z;
	float fRadius = fWidth / 3.0;
	float phana = (fLength*4.0) / 15.0;
	float phanb = (fLength*9.0) / 15.0;
	float phanc = (fLength) / 15.0;

		CreateHalfCylinder1(nSegment, fHeight, fRadius);
}
void Mesh::CreateShape3_3(float fLength, float fWidth, float fHeight)
{
	int nSegment = 36;
	int	idx = 0, idp = 0;
	float fAngle = PI / nSegment;
	float x, y, z;
	float fRadius = fWidth / 3.0;
	float phana = (fLength*4.0) / 15.0;
	float phanb = (fLength*9.0) / 15.0;
	float phanc = (fLength) / 15.0;

		CreateHalfCylinder2(nSegment, fHeight, fRadius, fLength);
}
void Mesh::CreateShape1_1(float fLength, float fWidth, float fHeight)
{
	int nSegment = 36;
	float fRadius = fLength / 4.0;
	float a = fHeight /4.0;
	float b = (fHeight * 3.0) / 4.0;
	int i;
	int idx = 0;
	numVerts = 16+nSegment*2+2;
	pt = new Point3[numVerts];
	pt[0].set(-fLength/2.0, a, fWidth/2.0);//A
	pt[1].set(fLength / 2.0, a, fWidth / 2.0);//B
	pt[2].set(fLength / 2.0, 0, fWidth / 2.0);//C
	pt[3].set(-fLength / 2.0, 0, fWidth / 2.0);//D
	pt[4].set(-fLength / 2.0, a, -fWidth / 2.0);//A'
	pt[5].set(fLength / 2.0, a, -fWidth / 2.0);//B'
	pt[6].set(fLength / 2.0, 0, -fWidth / 2.0);//C'
	pt[7].set(-fLength / 2.0, 0, -fWidth / 2.0);//D'

	pt[8].set(-fLength / 4.0, b, fWidth/2.0);//E
	pt[9].set(fLength / 4.0, b, fWidth / 2.0);//F
	pt[10].set(fLength / 4.0, a, fWidth / 2.0);//G
	pt[11].set(-fLength/4.0, a,fWidth/2.0);//H
	pt[12].set(-fLength / 4.0, b, -fWidth / 2.0);//E'
	pt[13].set(fLength / 4.0, b, -fWidth / 2.0);//F'
	pt[14].set(fLength / 4.0, a, -fWidth / 2.0);//G'
	pt[15].set(-fLength / 4.0, a, -fWidth / 2.0);//H'

	numFaces = 10+ nSegment * 3;
	face = new Face[numFaces];
//khối dưới
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 1;
	face[idx].vert[2].vertIndex = 2;
	face[idx].vert[3].vertIndex = 3;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 1;
	face[idx].vert[2].vertIndex = 5;
	face[idx].vert[3].vertIndex = 4;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4;
	face[idx].vert[1].vertIndex = 5;
	face[idx].vert[2].vertIndex = 6;
	face[idx].vert[3].vertIndex = 7;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 2;
	face[idx].vert[1].vertIndex = 3;
	face[idx].vert[2].vertIndex = 7;
	face[idx].vert[3].vertIndex = 6;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 3;
	face[idx].vert[2].vertIndex = 7;
	face[idx].vert[3].vertIndex = 4;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 1;
	face[idx].vert[1].vertIndex = 2;
	face[idx].vert[2].vertIndex = 6;
	face[idx].vert[3].vertIndex = 5;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//khối giữa
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 8;
	face[idx].vert[1].vertIndex = 9;
	face[idx].vert[2].vertIndex = 10;
	face[idx].vert[3].vertIndex = 11;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 12;
	face[idx].vert[1].vertIndex = 13;
	face[idx].vert[2].vertIndex = 14;
	face[idx].vert[3].vertIndex = 15;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 8;
	face[idx].vert[1].vertIndex = 11;
	face[idx].vert[2].vertIndex = 15;
	face[idx].vert[3].vertIndex = 12;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 9;
	face[idx].vert[1].vertIndex = 10;
	face[idx].vert[2].vertIndex = 14;
	face[idx].vert[3].vertIndex = 13;
	for (i = 0; i < face[idx].nVerts; i++)
		face[idx].vert[i].colorIndex = 0;
	idx++;
//khối cầu trên
	float	fAngle = PI / nSegment;
	float	x, y, z;
	int istart = 16;
	pt[16].set(0, b, fWidth / 2);
	for (i = 0; i < nSegment; i++) {
		x = fRadius * cos(fAngle*i);
		y = fRadius * sin(fAngle*i)+b;
		z = fWidth / 2;
		pt[istart+i + 1].set(x, y, z);

		z = -fWidth / 2;
		pt[istart+i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, b, -fWidth / 2);

	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = istart;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = istart+i + 2;
		else
			face[idx].vert[1].vertIndex = istart+1;
		face[idx].vert[2].vertIndex = istart+i + 1;
		idx++;
	}

	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex =istart+ i + 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex =istart+ i + 2;
		else
			face[idx].vert[1].vertIndex = istart+1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex =istart+ i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex =istart+ 1 + nSegment;
		face[idx].vert[1].vertIndex = istart+i + 1 + nSegment;
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
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}



