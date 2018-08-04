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
	static void drawTextOnScreen(string text);

	static void drawEllipsoid(float fA, float fB, float fC, unsigned int uiSlices, unsigned int uiStacks);
	static void drawCylinder(GLdouble baseRadius, GLdouble length);
	static void drawCone(GLdouble baseRadius, GLdouble length);
	static void debugDrawSomething(float x, float y, float z, int size);
	
	static void loadTexture(GLuint texture, const char* filePath);

	static float* getModelViewMatrix();
	static GLfloat* multMatrixVector4f(float* matrix, float* vector);
	static GLfloat* multMatrices4f(float* matrix1, float* matrix2);
	static bool gluInvertMatrix(const float m[16], float invOut[16]);

	static void maximizeWindow(string windowTitle);

private:
	Utils();
	~Utils();
};