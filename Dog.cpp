#include "Dog.h"


Dog::Dog() {}

Dog::Dog(int baseLength) {
	this->m_baseLength = baseLength;
	this->m_slices = 50;
	this->m_stacks = 50;
	this->m_bodyLength = this->m_baseLength;
	this->m_bodyHeight = this->m_baseLength * 0.3;
	this->m_bodyWidth = this->m_baseLength * 0.3;
	this->m_tailLength = this->m_bodyLength * 0.3;
	this->m_tailWidth = this->m_bodyWidth * 0.15;
	this->m_tailHeight = this->m_tailWidth;
	this->m_legX = this->m_bodyLength * 0.3f;
	this->m_legY = 0.0f;
	this->m_legZ = this->m_bodyWidth * 0.5f;
	
	//Create 4 legs
	for (int i = 0; i < 4; i++)
	{
		m_legs[i] = DogLeg(i, m_bodyLength, m_bodyHeight, m_bodyWidth);
	}
	this->m_neckLength = m_baseLength  *  0.45f;
	this->m_neckWidth = this->m_bodyWidth;
	this->m_neckHeight = this->m_bodyHeight * 0.4f;
	this->m_headRadius = this->m_neckLength * 0.5f;
	this->resetParameters(baseLength);

	m_viewInvMatrix = new float[16];
}

//Resets all angles
void Dog::resetParameters(int base) {
	m_neckAngleZ = 0;
	m_neckAngleY = 0;
	m_tailAngleZ = -30;
	m_tailAngleY = 0;
}


//Draw the whole dog
void Dog::draw() {
	glPushMatrix();
	glTranslatef(m_dogPosX, m_dogPosY, m_dogPosZ);

	this->drawAllLegs();
	this->drawTorso();
	this->drawTail();
	this->drawFace();
	
	glPopMatrix();
}

//Draw the body
void Dog::drawTorso() {
	glPushMatrix();

	glColor3fv(Color::Torso);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Torso);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::TorsoDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::Black);

	Utils::drawEllipsoid(m_bodyLength * 0.7, m_bodyHeight * 0.8, m_bodyWidth, 10, 10);
	glPopMatrix();
}

void Dog::drawFace() {
	glPushMatrix();
	
	//Neck
	glTranslatef(this->m_bodyLength * 0.65, m_bodyHeight / 2.0f, 0.0f);
	glPushMatrix();
	
	glColor3fv(Color::Neck);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Neck);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Neck);
	
	glRotatef(45 + this->m_neckAngleZ, 0, 0, 1); 
	glRotatef(90, 0, 1, 0);
	Utils::drawEllipsoid(m_neckWidth / 2, m_neckWidth * 0.4, m_neckLength * 0.5, 100, 100);

	glPopMatrix();

	//Head
	glRotatef(this->m_neckAngleZ, 0, 0, 1);
	glRotatef(this->m_neckAngleY, 0, 1, 0);

	glTranslatef(this->m_neckLength * 0.3, m_neckHeight * 0.8, 0.0f);
	glColor3fv(Color::Head);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Head);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Head);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::Black);
	Utils::drawSphere(m_headRadius, this->m_slices, this->m_stacks);

	//Ears
	glColor3fv(Color::Ear);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Ear);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Ear);
	
	glPushMatrix();
	glTranslatef(0, m_headRadius * 0.6, m_headRadius * 0.7);
	glRotatef(45, 1, 0, 0);	
	Utils::drawEllipsoid(1, 2, 1, this->m_slices, this->m_stacks); 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, m_headRadius * 0.6, -m_headRadius * 0.7);
	glRotatef(-45, 1, 0, 0);
	Utils::drawEllipsoid(1, 2, 1, this->m_slices, this->m_stacks);
	glPopMatrix();

	//Eyes
	glColor3fv(Color::Eye);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Eye);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Eye);

	glPushMatrix();
	glTranslatef(m_headRadius * 0.75, m_headRadius * 0.15, m_headRadius * 0.3);
	Utils::drawEllipsoid(1, 1, 1, this->m_slices, this->m_stacks);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_headRadius * 0.75, m_headRadius * 0.15, -m_headRadius * 0.3);
	Utils::drawEllipsoid(1, 1, 1, this->m_slices, this->m_stacks);
	glPopMatrix();

	//Mouth
	glColor3fv(Color::Mouth);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Mouth);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Mouth);

	glPushMatrix();
	glTranslatef(m_headRadius * 0.8, -m_headRadius * 0.55, 0);
	Utils::drawEllipsoid(0.5, 0.5, 1.5, this->m_slices, this->m_stacks);
	glPopMatrix();

	//Nose
	glColor3fv(Color::Nose);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Nose);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Nose);

	glPushMatrix();
	glTranslatef(m_headRadius * 0.8, -m_headRadius * 0.2, 0);

	//Calculate eye's position in world cooordinates (according to nose's position)
	this->calcEyesPosition();

	Utils::drawEllipsoid(2.5, 1, 1, m_slices, m_stacks);
	glPopMatrix();

	glPopMatrix();
}

void Dog::drawTail() {
	glPushMatrix();
	glTranslatef(-this->m_bodyLength / 2.0f - this->m_tailLength / 2.0f, 2, 0.0f);
	
	//Rotate according to user's selected angle
	glRotatef(m_tailAngleZ, 0, 0, 1);
	glRotatef(m_tailAngleY, 0, 1, 0);
	
	glColor3fv(Color::Tail);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Tail);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Tail);

	Utils::drawEllipsoid(this->m_tailLength, this->m_tailHeight, this->m_tailWidth, m_slices, m_stacks);
	glPopMatrix();
}

void Dog::drawAllLegs() {
	//Store the legs in order
	int v[4][3] = {
		{	 1,	 1,	 1 },
		{	-1,	-1,	 1 },
		{	 1,	 1,	-1 },
		{	-1,	-1,	-1 }
	};

	for (int i = 0; i < 4; i++) {
		glPushMatrix();

		glColor3fv(Color::Leg);
		glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Leg);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Leg);

		glTranslatef(v[i][0] * m_legX, v[i][1] * m_legY, v[i][2] * m_legZ);
		m_legs[i].draw();

		glPopMatrix();
	}
}

//Set the dog's position (center of torso position)
void Dog::setPosition(float x, float y, float z) {
	this->m_dogPosX = x;
	this->m_dogPosY = y;
	this->m_dogPosZ = z;
}


void Dog::setTailAngle(int yDiff, int zDiff)
{
	m_tailAngleY += yDiff;
	if (m_tailAngleY <= -40) {
		m_tailAngleY = -40;
	}
	else if (m_tailAngleY >= 40) {
		m_tailAngleY = 40;
	}

	m_tailAngleZ += zDiff;
	if (m_tailAngleZ <= -32) {
		m_tailAngleZ = -32;
	}
	else if (m_tailAngleZ >= 0) {
		m_tailAngleZ = 0;
	}
}

void Dog::setNeckAngle(int yDiff, int zDiff)
{
	m_neckAngleY += yDiff;
	if (m_neckAngleY <= -40) {
		m_neckAngleY = -40;
	}
	else if (m_neckAngleY >= 40) {
		m_neckAngleY = 40;
	}

	m_neckAngleZ += zDiff;
	if (m_neckAngleZ <= -32) {
		m_neckAngleZ = -32;
	}
	else if (m_neckAngleZ >= 45) {
		m_neckAngleZ = 45;
	}
}

GLfloat* Dog::getEyesPosition()
{
	return m_eyesPosition;
}

GLfloat* Dog::getEyesLookAt()
{
	return m_eyesLookAt;
}

void Dog::saveViewMatrix()
{
	//Get the current model view matrix which includes only the view transformation
	float* mat = Utils::getModelViewMatrix();
	
	//Calculate the inverse of the view matrix and save it (for later use of eye position calculation)
	Utils::gluInvertMatrix(mat, m_viewInvMatrix);

	mat = Utils::multMatrices4f(m_viewInvMatrix, mat);
}

void Dog::calcEyesPosition()
{
	//Get the model view matrix at the moment (just before the eyes are going to be drawn)
	float* mat = Utils::getModelViewMatrix();
	
	//Multiply by the inverse matrix of the view point itself in order to disable the effect of the camera view.
	/*
	V = view transformation matrix
	M = model transformation matrix
	Current model view matrix = V*M
	But we need just the model transformation matrix (M)
	If we multiply by V^-1 from the left then we'll get V^-1*V*M = I*M = M
	*/
	mat = Utils::multMatrices4f(m_viewInvMatrix, mat);

	//Multiply model transformation matrix by the unit vector in order to get the eye's position
	float vec[] = { 1, 1, 1, 1 };
	m_eyesPosition = Utils::multMatrixVector4f(mat, vec);


	//Now calculate also the lookAt point. We'll make the dog look straight (parallel to the nose)
	//To do so, translate by 10 on the X axis and then take again the modle-view matrix and calculate the new point's position
	glTranslatef(10, 0, 0);
	float* mat2 = Utils::getModelViewMatrix();
	mat2 = Utils::multMatrices4f(m_viewInvMatrix, mat2);
	m_eyesLookAt = Utils::multMatrixVector4f(mat2, vec);
	glTranslatef(-10, 0, 0);
}