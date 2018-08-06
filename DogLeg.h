#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <gl\GLU.h>
#include "consts.h"
#include "Utils.h"

class DogLeg
{
public:
	float m_upperAngle;		// Angle that upper leg makes with Torso Clock and negative
	float m_lowerAngle;		// Angle that lower leg makes with upper leg Clock and negative
	float m_feetAngle;		// Angle that feet makes with lower leg AntiClock and positive
	float m_feetLen;			// length of feet
	float m_feetThickness;	// thickness of feet
	float m_feetWidth;		// width of feet
	float m_upperLen;		// length of upper leg
	float m_upperThickness;	// thickness of upper leg
	float m_upperWidth;		// width of upper leg
	float m_lowerLen;		// length of lower leg
	float m_lowerThickness;	// thickness of lower leg
	float m_lowerWidth;		// width of lower leg

	DogLeg();
	DogLeg(int index, float bodyLength, float bodyHeight, float bodyWidth);

	void draw();
};

