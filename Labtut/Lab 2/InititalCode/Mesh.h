#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
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
	int		numVerts;
	Point3*		pt;
	
	int		numFaces;
	Face*		face;
public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateHalfCylinder1(int nSegment, float fHeight, float fRadius);
	void CreateHalfCylinder2(int nSegment, float fHeight, float fRadius,float fLength);
	void CreateShape4(float day,float rong, float cao);
	void CreateShape2(float fLength, float fWidth, float fHeight);
	void CreateShape3_1(float fLength, float fWidth, float fHeight);
	void CreateShape3_2(float fLength, float fWidth, float fHeight);
	void CreateShape3_3(float fLength, float fWidth, float fHeight);
	void CreateShape1_1(float fLength, float fWidth, float fHeight);
};

#endif