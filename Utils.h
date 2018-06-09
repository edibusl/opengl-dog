#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "consts.h"

class Utils
{
public:
	static float radians(float degrees);
	static float degreeToRadians(float degrees);
	static void drawCube(float length, float width, float height);
	static void drawSolidCube(float length/*x*/, float height/*y*/, float width/*z*/);
	static void drawSphere(float radius, float slices, float stacks);
	static float abs(float a);

private:
	Utils();
	~Utils();
};