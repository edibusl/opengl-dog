#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <string>
#include "consts.h"
#include "Color.h"

using namespace std;

enum FaceType { SOLID, WIRED };

class Utils
{
public:
	static float radians(float degrees);
	static float degreeToRadians(float degrees);
	static void drawCube(float length, float width, float height, FaceType faceType);

	static void drawSolidCube(float length/*x*/, float height/*y*/, float width/*z*/);
	static void drawWireCube(float length/*x*/, float height/*y*/, float width/*z*/);

	static void drawSphere(float radius, float slices, float stacks, FaceType faceType);
	static float abs(float a);
	static void drawText(GLfloat x, GLfloat y, GLfloat z, string text);

	static void drawEllipsoid(float fA, float fB, float fC, unsigned int uiSlices, unsigned int uiStacks);

	static void loadTexture(GLuint texture, const char* filePath);

private:
	Utils();
	~Utils();
};