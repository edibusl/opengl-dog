#include "DogLeg.h"


DogLeg::DogLeg()
{
}

DogLeg::DogLeg(int index, float bodyLength, float bodyHeight, float bodyWidth)
{

	this->m_upperAngle = -90;
	this->m_lowerAngle = 25;
	this->m_feetAngle = 90;

	this->m_upperLen = bodyLength * 0.30;
	this->m_upperThickness = bodyHeight * 0.2;
	this->m_upperWidth = bodyWidth * 0.2;

	this->m_lowerLen = bodyLength * 0.2;
	this->m_lowerThickness = bodyHeight * 0.2;
	this->m_lowerWidth = bodyWidth * 0.2;

	m_feetAngle = -m_upperAngle - m_lowerAngle;
	m_feetLen = m_lowerThickness * 1.5;
	m_feetThickness = m_lowerLen * 0.4f;
	m_feetWidth = m_lowerWidth;
	if (index % 2 == 0) {
		m_lowerAngle = 0.0f;
	}
}

void DogLeg::draw() {
	glPushMatrix();

	m_feetAngle = -m_lowerAngle - m_upperAngle;
	
	//Drawing upper leg
	glRotatef(this->m_upperAngle, 0.0, 0.0, 1.0);
	glTranslatef(this->m_upperLen / 2.0f, 0.0f, 0.0f);
	Utils::drawCube(this->m_upperLen, this->m_upperThickness, this->m_upperWidth);
	
	//Drawing lower leg
	glTranslatef(this->m_upperLen / 2.0f, 0.0f, 0.0f);
	glRotatef(this->m_lowerAngle, 0.0, 0.0, 1.0);
	glTranslatef(this->m_lowerLen / 2.0f, 0.0f, 0.0f);
	Utils::drawCube(this->m_lowerLen, this->m_lowerThickness, this->m_lowerWidth);
	
	//Drawing Feet
	glTranslatef(this->m_lowerLen / 2.0f, -this->m_lowerThickness / 2.0f, 0.0f);
	glRotatef(this->m_feetAngle, 0.0, 0.0, 1.0);
	glTranslatef(this->m_feetLen / 2.0f, 0.0f, 0.0f);
	Utils::drawCube(this->m_feetLen, this->m_feetThickness, this->m_feetWidth);

	glPopMatrix();
}