#include "Dog.h"



float Dog::ROT_ANGLE = -70.0f; // Angle of ratation after taking one step ahead.
Dog::Dog() {}


/*
Ctor - Takes the base length(Torso legth) and setup all angles.
*/
Dog::Dog(int base) {
	this->BASE = base;
	this->canMove = false;
	this->SLICES = 50;
	this->STACKS = 50;
	this->moveNum = 1;
	this->BODY_LENGTH = this->BASE;
	this->BODY_HEIGHT = this->BASE * 0.3;
	this->BODY_WIDTH = this->BASE * 0.3;
	this->TAIL_LENGTH = this->BODY_LENGTH * 0.3;
	this->TAIL_WIDTH = this->BODY_WIDTH * 0.15;
	this->TAIL_HEIGHT = this->TAIL_WIDTH;
	this->LEG_X = this->BODY_LENGTH * 0.3f;
	this->LEG_Y = 0.0f;
	this->LEG_Z = this->BODY_WIDTH * 0.5f;
	for (int i = 0; i < 4; i++) {
		legs[i] = DogLeg(-90.0, 25.0, -90.0, this->BODY_LENGTH * 0.30, this->BODY_HEIGHT * 0.2, this->BODY_WIDTH * 0.2,
			this->BODY_LENGTH * 0.20, this->BODY_HEIGHT * 0.2, this->BODY_WIDTH * 0.2);// Run a for loop here
		legs[i].FEET_ANGLE = -legs[i].UPPER_ANGLE - legs[i].LOWER_ANGLE;
		legs[i].FEET_LEN = legs[i].LOWER_THICKNESS * 1.5;
		legs[i].FEET_THICKNESS = legs[i].LOWER_LEN * 0.4f;
		legs[i].FEET_WIDTH = legs[i].LOWER_WIDTH;
		if (i % 2 == 0) {
			legs[i].LOWER_ANGLE = 0.0f;
		}
	}
	this->NECK_LENGTH = BASE  *  0.45f;
	this->NECK_WIDTH = this->BODY_WIDTH;
	this->NECK_HEIGHT = this->BODY_HEIGHT * 0.4f;
	this->HEAD_RADIUS = this->NECK_LENGTH * 0.5f;
	this->HEAD_HEIGHT = this->NECK_HEIGHT;
	this->HEAD_WIDTH = this->NECK_WIDTH;
	this->UPPER_HEAD_LENGTH = this->NECK_LENGTH / 2;
	this->UPPER_HEAD_HEIGHT = this->NECK_HEIGHT  *  2;
	this->UPPER_HEAD_WIDTH = this->NECK_WIDTH;
	this->EYE_RADIUS = this->UPPER_HEAD_HEIGHT * 0.20;
	this->resetParameters(base);

	this->m_faceType = FaceType::SOLID;
	m_viewInvMatrix = new float[16];
}

//Resets all angles
void Dog::resetParameters(int base) {
	m_neckAngleZ = 0;
	m_neckAngleY = 0;
	m_tailAngleZ = -30;
	m_tailAngleY = 0;
}

//Resets all leg angles
void Dog::resetAngles() {
	for (int i = 0; i < 4; i++) {
		legs[i] = DogLeg(-90.0, 25.0, -90.0, this->BODY_LENGTH * 0.40, this->BODY_HEIGHT * 0.4, this->BODY_WIDTH * 0.4,
			this->BODY_LENGTH * 0.25, this->BODY_HEIGHT * 0.4, this->BODY_WIDTH * 0.4);// Run a for loop here
		legs[i].FEET_ANGLE = -legs[i].UPPER_ANGLE - legs[i].LOWER_ANGLE;
		legs[i].FEET_LEN = legs[i].LOWER_THICKNESS * 1.5;
		legs[i].FEET_THICKNESS = legs[i].LOWER_LEN * 0.4f;
		legs[i].FEET_WIDTH = legs[i].LOWER_WIDTH;
		if (i % 2 == 0) {
			legs[i].LOWER_ANGLE = 0.0f;
		}
	}
}

//Draw the whole dog
void Dog::draw() {
	glPushMatrix();
	glTranslatef(x_pos, y_pos, z_pos);
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
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::White);

	Utils::drawEllipsoid(BODY_LENGTH * 0.7, BODY_HEIGHT * 0.8, BODY_WIDTH, 10, 10);
	glPopMatrix();
}

void Dog::drawFace() {
	glPushMatrix();
	
	//Neck
	glTranslatef(this->BODY_LENGTH * 0.65, BODY_HEIGHT / 2.0f, 0.0f);
	glPushMatrix();
	
	glColor3fv(Color::Neck);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Neck);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Neck);
	
	glRotatef(45 + this->m_neckAngleZ, 0, 0, 1); 
	glRotatef(90, 0, 1, 0);
	Utils::drawEllipsoid(NECK_WIDTH / 2, NECK_WIDTH * 0.4, NECK_LENGTH * 0.5, 100, 100);

	glPopMatrix();

	//Head
	glRotatef(this->m_neckAngleZ, 0, 0, 1);
	glRotatef(this->m_neckAngleY, 0, 1, 0);

	glTranslatef(this->NECK_LENGTH * 0.3, NECK_HEIGHT * 0.8, 0.0f);
	glColor3fv(Color::Head);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Head);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Head);
	Utils::drawSphere(HEAD_RADIUS, this->SLICES, this->STACKS, FaceType::SOLID);

	//Ears
	glColor3fv(Color::Ear);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Ear);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Ear);
	
	glPushMatrix();
	glTranslatef(0, HEAD_RADIUS * 0.6, HEAD_RADIUS * 0.7);
	glRotatef(45, 1, 0, 0);	
	Utils::drawEllipsoid(1, 2, 1, this->SLICES, this->STACKS); 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, HEAD_RADIUS * 0.6, -HEAD_RADIUS * 0.7);
	glRotatef(-45, 1, 0, 0);
	Utils::drawEllipsoid(1, 2, 1, this->SLICES, this->STACKS);
	glPopMatrix();

	//Eyes
	glColor3fv(Color::Eye);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Eye);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Eye);

	glPushMatrix();
	glTranslatef(HEAD_RADIUS * 0.75, HEAD_RADIUS * 0.15, HEAD_RADIUS * 0.3);
	Utils::drawEllipsoid(1, 1, 1, this->SLICES, this->STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(HEAD_RADIUS * 0.75, HEAD_RADIUS * 0.15, -HEAD_RADIUS * 0.3);
	Utils::drawEllipsoid(1, 1, 1, this->SLICES, this->STACKS);
	glPopMatrix();

	//Mouth
	glColor3fv(Color::Mouth);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Mouth);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Mouth);

	glPushMatrix();
	glTranslatef(HEAD_RADIUS * 0.8, -HEAD_RADIUS * 0.55, 0);
	Utils::drawEllipsoid(0.5, 0.5, 1.5, this->SLICES, this->STACKS);
	glPopMatrix();

	//Nose
	glColor3fv(Color::Nose);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Nose);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Nose);

	glPushMatrix();
	glTranslatef(HEAD_RADIUS * 0.8, -HEAD_RADIUS * 0.2, 0);

	//Calculate eye's position in world cooordinates (according to nose's position)
	this->calcEyesPosition();

	Utils::drawEllipsoid(2.5, 1, 1, SLICES, STACKS);
	glPopMatrix();

	glPopMatrix();
}

void Dog::drawTail() {
	glPushMatrix();
	glTranslatef(-this->BODY_LENGTH / 2.0f - this->TAIL_LENGTH / 2.0f, 2, 0.0f);
	
	//Rotate according to user's selected angle
	glRotatef(m_tailAngleZ, 0, 0, 1);
	glRotatef(m_tailAngleY, 0, 1, 0);
	
	glColor3fv(Color::Tail);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Tail);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Tail);

	//Utils::drawCube(this->TAIL_LENGTH, this->TAIL_HEIGHT, this->TAIL_WIDTH, this->m_faceType);
	Utils::drawEllipsoid(this->TAIL_LENGTH, this->TAIL_HEIGHT, this->TAIL_WIDTH, SLICES, STACKS);
	glPopMatrix();
}

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

		glColor3fv(Color::Leg);
		glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Leg);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Leg);

		glTranslatef(v[i][0] * LEG_X, v[i][1] * LEG_Y, v[i][2] * LEG_Z);
		legs[i].FEET_ANGLE = -legs[i].LOWER_ANGLE - legs[i].UPPER_ANGLE;
		legs[i].drawLeg();
		glPopMatrix();
	}
}

//Set the dog's position (center of mass position)
void Dog::setPosition(float x, float y, float z) {
	this->x_pos = x;
	this->y_pos = y;
	this->z_pos = z;
}

//Change the angle between legs while dog moves.
void Dog::move() {
	int v[4][3] = {
		{ 1,1,1 },
	{ -1,-1,1 },
	{ 1,1,-1 },
	{ -1,-1,-1 }
	};
	//First move the Torso
	this->x_pos += this->direction * this->legs[0].UPPER_LEN / tan(Utils::degreeToRadians(Utils::abs(Dog::ROT_ANGLE)));
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