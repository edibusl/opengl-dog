#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <gl\GLU.h>
#include "consts.h"
#include "Utils.h"

class Furniture
{
private:
	int m_PosX;
	int m_PosY;
	int m_PosZ;

	static const GLfloat TableLegSizeX;
	static const GLfloat TableLegSizeY;
	static const GLfloat TableLegSizeZ;
	static const GLfloat TableSurfaceSize;
	static const GLfloat TableSurfaceThickness;
	static const GLfloat TeapotSize;
public:
	Furniture(int initialPosX, int initialPosY, int initialPosZ);
	~Furniture();

	void draw();
};

