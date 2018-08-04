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
	int m_width;
	int m_height;
	GLuint m_textureWall;
	GLuint m_textureFloor;
	GLuint m_textureCeiling;

public:
	Room(int width, int height);
	void draw();

private:
	void drawWall();
	void drawHorizontalWall();
};

