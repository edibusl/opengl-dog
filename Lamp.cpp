#include "Lamp.h"

Lamp::Lamp()
{
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

void Lamp::setLighting(boolean enabled)
{
	if (!enabled) {
		glDisable(GL_LIGHT2);

		return;
	}

	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightPosition[] = { m_positionX, m_positionY - 15, m_positionZ, 1 };
	GLfloat lightDirection[] = { 10, 10, 10, 1 };

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Color::Black);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Color::White);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10.0); //30 degress cutoff angle
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.5); //attenuation
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDirection);
}

void Lamp::rotate(int x, int y, int z) {
	m_angleX += x;
	m_angleY += y;
	m_angleZ += z;
}