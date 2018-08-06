#include "Lamp.h"

const int Lamp::CABLE_LENGTH = 60;

Lamp::Lamp()
{
	m_intensity = 0.35;

	//Initial spotlight direction - direct to the dog's body
	m_directionX = -20;
	m_directionZ = -20;
}

void Lamp::draw(int x, int y, int z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;

	//Translate whole lamp's position
	glPushMatrix();
	glTranslatef(m_positionX, m_positionY, m_positionZ);

	//Lamp's cable
	glPushMatrix();

	glColor3fv(Color::Black);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::Black);

	glRotatef(90, 1, 0, 0);
	Utils::drawCylinder(0.5, CABLE_LENGTH);
	glPopMatrix();
	
	//Round lamp
	glPushMatrix();
	glTranslatef(0, -CABLE_LENGTH - 3, 0);
	
	glColor3fv(Color::Yellow);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::Yellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::Yellow);


	Utils::drawSphere(4, 32, 32);
	glPopMatrix();

	//Draw the lamp's base cone
	glPushMatrix();

	glColor3fv(Color::DarkBlue);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::DarkBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::DarkBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::DarkBlue);

	glTranslatef(0, -CABLE_LENGTH + 9, 0);
	glRotatef(90, 1, 0, 0);
	Utils::drawCone(6, 13);
	glPopMatrix();

	//Remove lamp position translation
	glPopMatrix();
}

void Lamp::setLighting()
{
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0); //30 degress cutoff angle

	//Position
	GLfloat lightPosition[] = { m_positionX, m_positionY - CABLE_LENGTH - 10, m_positionZ, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

	//Direction - the spotlight points down
	GLfloat directionPoint[] = { m_directionX, 0, m_directionZ, 1 };
	GLfloat directionVector[] = { directionPoint[0] - m_positionX, directionPoint[1] - m_positionY, directionPoint[2] - m_positionZ, 1 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, directionVector);

	//Intensity (diffuse / specular)
	this->setIntensity(0);

	glEnable(GL_LIGHT1);
}

void Lamp::setIntensity(float diff)
{
	m_intensity += diff;
	if (m_intensity > 0.35)
	{
		m_intensity = 0.35;
	}
	else if (m_intensity < 0)
	{
		m_intensity = 0;
	}

	float intensity[] = { m_intensity, m_intensity, m_intensity, 1 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, intensity);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, intensity);
}

void Lamp::setLightDirection(int x, int z)
{
	m_directionX += x;
	m_directionZ += z;
}