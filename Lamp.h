#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <gl\GLU.h>
#include "consts.h"
#include "Utils.h"

class Lamp
{
private:
	static const int CABLE_LENGTH;

private:
	int m_positionX;
	int m_positionY;
	int m_positionZ;
	int m_directionX;
	int m_directionY;
	int m_directionZ;
	int m_angleX;
	int m_angleY;
	int m_angleZ;	

public:
	Lamp();
	void draw(int x, int y, int z);
	void setLighting(boolean enabled);
	void rotate(int x, int y, int z);
	void setLightPosition(int x, int y, int z);
	void setLightDirection(int x, int y, int z);
};