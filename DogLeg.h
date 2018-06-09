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
	float upper_leg_x;		// x coordinate of the upper leg  in world coordinates
	float upper_leg_y;		// y coordinate of the upper leg in world coordinates
	float upper_leg_z;		// z coordinate of the upper leg in world coordinates
	float lower_leg_x;		// x coordinate of the lower leg in world coordinates
	float lower_leg_y;		// y coordinate of the lower leg in world coordinates
	float lower_leg_z;		// z coordinate of the lower leg in world coordinates
	float feet_x;			// x coordinate of the feet in world coordinates
	float feet_y;			// y coordinate of the feet  in world coordinates
	float feet_z;			// z coordinate of the feet leg in world coordinates
	float UPPER_ANGLE;		// Angle that upper leg makes with Torso Clock and negative
	float LOWER_ANGLE;		// Angle that lower leg makes with upper leg Clock and negative
	float FEET_ANGLE;		// Angle that feet makes with lower leg AntiClock and positive
	float FEET_LEN;			// length of feet
	float FEET_THICKNESS;	// thickness of feet
	float FEET_WIDTH;		// width of feet
	float UPPER_LEN;		// length of upper leg
	float UPPER_THICKNESS;	// thickness of upper leg
	float UPPER_WIDTH;		// width of upper leg
	float LOWER_LEN;		// length of lower leg
	float LOWER_THICKNESS;	// thickness of lower leg
	float LOWER_WIDTH;		// width of lower leg

	DogLeg();
	DogLeg(float UPPER_ANGLE, float LOWER_ANGLE, float FEET_ANGLE,
		float UPPER_LEN, float UPPER_THICKNESS, float UPPER_WIDTH,
		float LOWER_LEN, float LOWER_THICKNESS, float LOWER_WIDTH);
	void drawLeg();
};

