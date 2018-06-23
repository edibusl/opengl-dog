#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <gl\GLU.h>
#include "consts.h"
#include "Utils.h"

class Room
{
private:
	static int WALL_THICKNESS;
	float m_size;
	GLuint m_textureWall;
	GLuint m_textureFloor;
	GLuint m_textureCeiling;

public:
	Room(int size);
	void draw();

private:
	void drawWall();
};

