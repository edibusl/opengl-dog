#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include "consts.h"
#include "Utils.h"
#include "DogLeg.h"

class Dog
{
private:
	int moveNum;
	int direction;
	static float ROT_ANGLE;//angle made w.r.t hip when the animal moves
	float BASE;
	float SLICES;
	float STACKS;
	bool canMove;
	float LEG_X;//Distance of leg from the center of the body in X direction
	float LEG_Y;//Distance of leg from the center of the body in Y direction
	float LEG_Z;//Distance of leg from the center of the body in Z direction
	float BODY_LENGTH;
	float BODY_WIDTH;
	float NECK_ANGLE;
	float HEAD_ANGLE;
	float NECK_LENGTH;
	float NECK_HEIGHT;
	float NECK_WIDTH;
	float HEAD_HEIGHT;
	float HEAD_LENGTH;
	float HEAD_WIDTH;
	float UPPER_HEAD_HEIGHT;
	float UPPER_HEAD_LENGTH;
	float UPPER_HEAD_WIDTH;
	float EYE_RADIUS;
	float TAIL_LENGTH;
	float TAIL_WIDTH;
	float TAIL_HEIGHT;
	float x_pos;
	float z_pos;

	FaceType m_faceType;

public:
	float BODY_HEIGHT;
	DogLeg legs[4];
	float y_pos;

public:
	Dog();
	Dog(int base);
	void draw();
	void setPosition(float x, float y, float z);

private:	
	void resetParameters(int base);
	void drawTorso();
	void drawFace();
	void drawTail();
	void drawAllLegs();
	void move();
	void resetAngles();
};

