#include "Dog.h"



float Dog::ROT_ANGLE = -70.0f; // Angle of ratation after taking one step ahead.
Dog::Dog() {} // Default construtor of Dog Class

					/*
					****************************************************************************************************
					Dog::resetAngle: Resets all NECK_ANGLE and HEAD_ANGLE.
					****************************************************************************************************
					*/
void Dog::resetParameters(int base) {
	this->NECK_ANGLE = 35.0;// Angle between neck and body in dergees
	this->HEAD_ANGLE = -this->NECK_ANGLE;
}

/*
****************************************************************************************************
Dog::resetAngle: Resets all leg angle.
****************************************************************************************************
*/
void Dog::resetAngles() {
	for (int i = 0; i < 4; i++) {
		legs[i] = DogLeg(-90.0, 25.0, -90.0, this->BODY_LENGTH*0.40, this->BODY_HEIGHT*0.4, this->BODY_WIDTH*0.4,
			this->BODY_LENGTH*0.25, this->BODY_HEIGHT*0.4, this->BODY_WIDTH*0.4);// Run a for loop here
		legs[i].FEET_ANGLE = -legs[i].UPPER_ANGLE - legs[i].LOWER_ANGLE;
		legs[i].FEET_LEN = legs[i].LOWER_THICKNESS*1.5;
		legs[i].FEET_THICKNESS = legs[i].LOWER_LEN*0.4f;
		legs[i].FEET_WIDTH = legs[i].LOWER_WIDTH;
		if (i % 2 == 0) {
			legs[i].LOWER_ANGLE = 0.0f;
		}
	}

}
/*
****************************************************************************************************
Dog::Dog: Constructor of animal class. It takes the base length(Torso legth). It responsible
for setting up all angles.
****************************************************************************************************
*/
Dog::Dog(int base) {
	this->BASE = base;
	this->canMove = false;
	this->SLICES = 10;
	this->STACKS = 10;
	this->moveNum = 1;
	this->BODY_LENGTH = this->BASE;
	this->BODY_HEIGHT = this->BASE*0.3;
	this->BODY_WIDTH = this->BASE*0.3;
	this->TAIL_LENGTH = this->BODY_LENGTH*0.6;
	this->TAIL_WIDTH = this->BODY_WIDTH*0.2;
	this->TAIL_HEIGHT = this->TAIL_WIDTH;
	this->LEG_X = this->BODY_LENGTH*0.3f;
	this->LEG_Y = 0.0f;
	this->LEG_Z = this->BODY_WIDTH*0.5f;
	for (int i = 0; i < 4; i++) {
		legs[i] = DogLeg(-90.0, 25.0, -90.0, this->BODY_LENGTH*0.30, this->BODY_HEIGHT*0.2, this->BODY_WIDTH*0.2,
			this->BODY_LENGTH*0.20, this->BODY_HEIGHT*0.2, this->BODY_WIDTH*0.2);// Run a for loop here
		legs[i].FEET_ANGLE = -legs[i].UPPER_ANGLE - legs[i].LOWER_ANGLE;
		legs[i].FEET_LEN = legs[i].LOWER_THICKNESS*1.5;
		legs[i].FEET_THICKNESS = legs[i].LOWER_LEN*0.4f;
		legs[i].FEET_WIDTH = legs[i].LOWER_WIDTH;
		if (i % 2 == 0) {
			legs[i].LOWER_ANGLE = 0.0f;
		}
	}
	this->NECK_LENGTH = BASE * 0.45f;
	this->NECK_WIDTH = this->BODY_WIDTH;
	this->NECK_HEIGHT = this->BODY_HEIGHT*0.4f;
	this->HEAD_LENGTH = this->NECK_LENGTH*0.5f;
	this->HEAD_HEIGHT = this->NECK_HEIGHT;
	this->HEAD_WIDTH = this->NECK_WIDTH;
	this->UPPER_HEAD_LENGTH = this->NECK_LENGTH / 2;
	this->UPPER_HEAD_HEIGHT = this->NECK_HEIGHT * 2;
	this->UPPER_HEAD_WIDTH = this->NECK_WIDTH;
	this->EYE_RADIUS = this->UPPER_HEAD_HEIGHT*0.20;
	this->resetParameters(base);
}

/*
***********************************************************************************************
Dog::drawDog: This function is used to draw the whole animal.
***********************************************************************************************
*/
void Dog::draw() {
	glPushMatrix();
	glTranslatef(x_pos, y_pos, z_pos);
	this->drawTorso();
	this->drawTail();
	this->drawFace();
	this->drawAllLegs();
	glPopMatrix();
}

/*
***********************************************************************************************
Dog::drawTorso: This function is used to draw the main body of the animal
***********************************************************************************************
*/
void Dog::drawTorso() {
	glPushMatrix();
	glColor3f(0.5f, 0.35f, 0.05f);
	Utils::drawCube(BODY_LENGTH, BODY_HEIGHT, BODY_WIDTH);
	glPopMatrix();
}
/*
***********************************************************************************************
Dog::drawFace: This function is used to draw the face of the animal
***********************************************************************************************
*/
void Dog::drawFace() {
	glPushMatrix();
	//Creating Neck
	glTranslatef(this->BODY_LENGTH*0.65, BODY_HEIGHT / 2.0f, 0.0f);
	glRotatef(this->NECK_ANGLE, 0.0f, 0.0f, 1.0f);
	glColor3f(0.5f, 0.35f, 0.05f);
	Utils::drawCube(NECK_LENGTH, NECK_HEIGHT, NECK_WIDTH);
	//Creating Face
	glRotatef(this->HEAD_ANGLE, 0.0f, 0.0f, 1.0f);
	glTranslatef(this->NECK_LENGTH*0.75, NECK_HEIGHT, 0.0f);
	glColor3f(0.5f, 0.35f, 0.05f);
	Utils::drawCube(HEAD_LENGTH, HEAD_HEIGHT, HEAD_WIDTH);
	//Creating Mouth
	glPushMatrix();
	glTranslatef(this->HEAD_LENGTH*0.5, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	Utils::drawCube(HEAD_LENGTH*0.2, HEAD_HEIGHT, HEAD_WIDTH);
	glColor3f(0.5f, 0.35f, 0.05f);
	Utils::drawCube(HEAD_LENGTH*0.2, HEAD_HEIGHT*0.1, HEAD_WIDTH);
	glPopMatrix();
	//Drawing upper head
	glTranslatef(-1 * this->NECK_LENGTH*0.5, this->NECK_HEIGHT*0.25f, 0.0f);
	glColor3f(0, 0, 0);
	glPointSize(10);
	glColor3f(0.5f, 0.35f, 0.05f);
	Utils::drawCube(UPPER_HEAD_LENGTH, UPPER_HEAD_HEIGHT, UPPER_HEAD_WIDTH);
	//Drawing Eyes
	glPushMatrix();
	glTranslatef(this->UPPER_HEAD_LENGTH*0.5, this->UPPER_HEAD_HEIGHT*0.25, -this->UPPER_HEAD_WIDTH*0.40);
	glColor3f(0.0f, 0.0f, 0.0f);
	Utils::drawSphere(this->EYE_RADIUS, this->SLICES, this->STACKS);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(this->UPPER_HEAD_LENGTH*0.5, this->UPPER_HEAD_HEIGHT*0.25, this->UPPER_HEAD_WIDTH*0.40);
	glColor3f(0.0f, 0.0f, 0.0f);
	Utils::drawSphere(this->EYE_RADIUS, this->SLICES, this->STACKS);
	glPopMatrix();
	glPopMatrix();
}
/*
***********************************************************************************************
Dog::drawTail: This function is used to draw the tail of the animal
***********************************************************************************************
*/
void Dog::drawTail() {
	glPushMatrix();
	glTranslatef(-this->BODY_LENGTH / 2.0f - this->TAIL_LENGTH / 2.0f, 0.0f, 0.0f);
	glColor3f(0.5f, 0.35f, 0.05f);
	Utils::drawCube(this->TAIL_LENGTH, this->TAIL_HEIGHT, this->TAIL_WIDTH);
	glPopMatrix();
}
/*
***********************************************************************************************
Dog::drawAllLegs: This function is used to draw all 4 legs of the animal
***********************************************************************************************
*/
void Dog::drawAllLegs() {
	//For storing the legs in order
	int v[4][3] = {
		{ 1,1,1 },
	{ -1,-1,1 },
	{ 1,1,-1 },
	{ -1,-1,-1 }
	};
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glColor3f(0.5f, 0.35f, 0.5f);
		glTranslatef(v[i][0] * LEG_X, v[i][1] * LEG_Y, v[i][2] * LEG_Z);
		legs[i].FEET_ANGLE = -legs[i].LOWER_ANGLE - legs[i].UPPER_ANGLE;
		legs[i].drawLeg();
		glPopMatrix();
	}
}

/*
***********************************************************************************************
Dog::setPosition: This function is used to set the animals position (center of mass position)
***********************************************************************************************
*/
void Dog::setPosition(float x, float y, float z) {
	this->x_pos = x;
	this->y_pos = y;
	this->z_pos = z;
}

/*
***********************************************************************************************
Dog::move: This function is used to change the angle between legs while animal moves.
It is responsible of the movement of the animal.
***********************************************************************************************
*/
void Dog::move() {
	int v[4][3] = {
		{ 1,1,1 },
	{ -1,-1,1 },
	{ 1,1,-1 },
	{ -1,-1,-1 }
	};
	//First move the Torso
	this->x_pos += this->direction*this->legs[0].UPPER_LEN / tan(Utils::degreeToRadians(Utils::abs(Dog::ROT_ANGLE)));
	if (moveNum == 1 && this->direction == 1) {
		//Move Front Face
		legs[0].UPPER_ANGLE = Dog::ROT_ANGLE;
		legs[0].LOWER_ANGLE = -90.0f - Dog::ROT_ANGLE;
		legs[1].UPPER_ANGLE = Dog::ROT_ANGLE;

		//Keep back face as it is
		legs[2].LOWER_ANGLE = -90.0f - Dog::ROT_ANGLE;
		legs[2].UPPER_ANGLE = -180.0f - Dog::ROT_ANGLE;
		legs[3].UPPER_ANGLE = -180.0f - Dog::ROT_ANGLE;
	}
	if ((moveNum == 0 && this->direction == 1)) {
		//Move Front Face
		legs[2].UPPER_ANGLE = Dog::ROT_ANGLE;
		legs[2].LOWER_ANGLE = -90.0f - Dog::ROT_ANGLE;
		legs[3].UPPER_ANGLE = Dog::ROT_ANGLE;

		//Keep back face as it is
		legs[0].LOWER_ANGLE = -90.0f - Dog::ROT_ANGLE;
		legs[0].UPPER_ANGLE = -180.0f - Dog::ROT_ANGLE;
		legs[1].UPPER_ANGLE = -180.0f - Dog::ROT_ANGLE;
		//this->resetAngles();
	}
	if (moveNum == 0 && this->direction == -1) {
		//Move Front Face
		legs[0].UPPER_ANGLE = Dog::ROT_ANGLE;
		legs[0].LOWER_ANGLE = -90.0f - Dog::ROT_ANGLE;
		legs[1].UPPER_ANGLE = Dog::ROT_ANGLE;

		//Keep back face as it is
		legs[2].LOWER_ANGLE = -90.0f - Dog::ROT_ANGLE;
		legs[2].UPPER_ANGLE = -180.0f - Dog::ROT_ANGLE;
		legs[3].UPPER_ANGLE = -180.0f - Dog::ROT_ANGLE;
	}
	if ((moveNum == 1 && this->direction == -1)) {
		//Move Front Face
		legs[2].UPPER_ANGLE = Dog::ROT_ANGLE;
		legs[2].LOWER_ANGLE = -90.0f - Dog::ROT_ANGLE;
		legs[3].UPPER_ANGLE = Dog::ROT_ANGLE;

		//Keep back face as it is
		legs[0].LOWER_ANGLE = -90.0f - Dog::ROT_ANGLE;
		legs[0].UPPER_ANGLE = -180.0f - Dog::ROT_ANGLE;
		legs[1].UPPER_ANGLE = -180.0f - Dog::ROT_ANGLE;
		//this->resetAngles();
	}
	if (moveNum == 2) {
		//Set back to the original position
		this->resetAngles();
	}
	moveNum++;
	moveNum %= 3;
	//this->drawDog();
}