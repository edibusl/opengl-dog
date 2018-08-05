#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <gl\GLU.h>
#include "consts.h"
#include "Utils.h"

class Camera
{
public:
	static float EYE_X;
	static float EYE_Y;
	static float EYE_Z;
	static float LOOK_AT_X;
	static float LOOK_AT_Y;
	static float LOOK_AT_Z;
	static float VUP_X;
	static float VUP_Y;
	static float VUP_Z;
	static float ANGLE;
	static float Z_NEAR;
	static float Z_FAR;

	static void init();
	static void changePosition(int x, int y, int z);
	static void changeLookingPoint(int x, int y, int z);
	static void lookAt();
	static void lookAt(float eyeX, float eyeY, float eyeZ, float lookAtX, float lookAtY, float lookAtZ);

private:
	Camera();
	~Camera();
};