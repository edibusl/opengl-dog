#include "DogLeg.h"


DogLeg::DogLeg()
{
}

DogLeg::DogLeg(float UPPER_ANGLE, float LOWER_ANGLE, float FEET_ANGLE,
	float UPPER_LEN, float UPPER_THICKNESS, float UPPER_WIDTH,
	float LOWER_LEN, float LOWER_THICKNESS, float LOWER_WIDTH) {
	this->UPPER_ANGLE = UPPER_ANGLE;
	this->LOWER_ANGLE = LOWER_ANGLE;
	this->FEET_ANGLE = FEET_ANGLE;
	this->UPPER_LEN = UPPER_LEN;
	this->UPPER_THICKNESS = UPPER_THICKNESS;
	this->UPPER_WIDTH = UPPER_WIDTH;
	this->LOWER_LEN = LOWER_LEN;
	this->LOWER_THICKNESS = LOWER_THICKNESS;
	this->LOWER_WIDTH = LOWER_WIDTH;
}

void DogLeg::drawLeg() {
	glPushMatrix();
	
	//Drawing upper leg
	glRotatef(this->UPPER_ANGLE, 0.0, 0.0, 1.0);
	glTranslatef(this->UPPER_LEN / 2.0f, 0.0f, 0.0f);
	Utils::drawCube(this->UPPER_LEN, this->UPPER_THICKNESS, this->UPPER_WIDTH, FaceType::SOLID);
	
	//Drawing lower leg
	glTranslatef(this->UPPER_LEN / 2.0f, 0.0f, 0.0f);
	glRotatef(this->LOWER_ANGLE, 0.0, 0.0, 1.0);
	glTranslatef(this->LOWER_LEN / 2.0f, 0.0f, 0.0f);
	Utils::drawCube(this->LOWER_LEN, this->LOWER_THICKNESS, this->LOWER_WIDTH, FaceType::SOLID);
	
	//Drawing Feet
	glTranslatef(this->LOWER_LEN / 2.0f, -this->LOWER_THICKNESS / 2.0f, 0.0f);
	glRotatef(this->FEET_ANGLE, 0.0, 0.0, 1.0);
	glTranslatef(this->FEET_LEN / 2.0f, 0.0f, 0.0f);
	Utils::drawCube(this->FEET_LEN, this->FEET_THICKNESS, this->FEET_WIDTH, FaceType::SOLID);

	glPopMatrix();
}