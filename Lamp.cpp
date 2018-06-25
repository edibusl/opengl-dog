#include "Lamp.h"

Lamp::Lamp()
{
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	m_angleX = 0;
	m_angleY = 0;
	m_angleZ = 0;
}

void Lamp::draw(int x, int y, int z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;

	//Translate whole lamp's position
	glPushMatrix();
	glTranslatef(x, y, z);

	//Rotate whole lamp according to angle
	glPushMatrix();
	glRotatef(m_angleX, 1, 0, 0);
	glRotatef(m_angleY, 0, 1, 0);
	glRotatef(m_angleZ, 0, 0, 1);

	//Lamp's cable
	glPushMatrix();
	glColor3fv(Color::Black);
	glRotatef(90, 1, 0, 0);
	Utils::drawCylinder(0.5, 15);
	glPopMatrix();
	
	//Round lamp
	glPushMatrix();
	glTranslatef(0, -18, 0);
	glColor3fv(Color::Yellow);
	Utils::drawSphere(4, 32, 32, FaceType::SOLID);
	glPopMatrix();

	//Draw the lamp's base cone
	glPushMatrix();
	glColor3fv(Color::Black);
	glTranslatef(0, -7, 0);
	glRotatef(90, 1, 0, 0);
	Utils::drawCone(6, 13);
	glPopMatrix();

	//Remove lamp position translation
	glPopMatrix();

	//Remove lamp angle rotation
	glPopMatrix();
}

void Lamp::setLighting()
{
	GLfloat colorWhite[] = { 0.5, 0.5, 0.5, 1.0 };

	GLfloat lightPosition1[] = { m_positionX, m_positionY - 15, m_positionZ, 1 };
	GLfloat lightDirection1[] = { 10, 10, 10 };

	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, colorWhite);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, colorWhite);
	glLightfv(GL_LIGHT1, GL_SPECULAR, colorWhite);


	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDirection1);


	return;
	//############################################################################

	//Set global ambient light
	glEnable(GL_LIGHTING);
	/*GLfloat globalAmbient[] = { 0.9, 0.9, 0.9, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);*/

	//Spot light
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
	GLfloat whiteColor[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat lightPosition[] = { m_positionX, m_positionY - 15, m_positionZ, 0 };
	GLfloat lightDirection[] = { 100, 100, 100 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.5);
}

void Lamp::rotate(int x, int y, int z) {
	m_angleX += x;
	m_angleY += y;
	m_angleZ += z;
}