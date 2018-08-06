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
	float m_baseLength;
	float m_slices;
	float m_stacks;
	float m_legX; //Distance of leg from the center of the body in X direction
	float m_legY; //Distance of leg from the center of the body in Y direction
	float m_legZ; //Distance of leg from the center of the body in Z direction
	float m_bodyLength;
	float m_bodyWidth;
	
	float m_neckLength;
	float m_neckHeight;
	float m_neckWidth;
	float m_headRadius;
	float m_tailLength;
	float m_tailWidth;
	float m_tailHeight;

	float m_dogPosX;
	float m_dogPosZ;
	float m_dogPosY;

	float m_neckAngleZ;
	float m_neckAngleY;
	float m_tailAngleY;
	float m_tailAngleZ;
	GLfloat* m_eyesPosition;
	GLfloat* m_eyesLookAt;
	float* m_viewInvMatrix; //Inverted matrix of the view tranformation (the model-view matrix right after applying lookAt)

public:
	float m_bodyHeight;
	DogLeg m_legs[4];

public:
	Dog();
	Dog(int baseLength);
	void draw();
	void setPosition(float x, float y, float z);
	void setTailAngle(int yDiff, int zDiff);
	void setNeckAngle(int yDiff, int zDiff);
	GLfloat* getEyesPosition();
	GLfloat* getEyesLookAt();
	void saveViewMatrix();

private:	
	void resetParameters(int base);
	void drawTorso();
	void drawFace();
	void drawTail();
	void drawAllLegs();
	void calcEyesPosition();
};