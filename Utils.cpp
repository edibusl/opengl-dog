#include "Utils.h"

Utils::Utils()
{
}


Utils::~Utils()
{
}


float Utils::radians(float degrees) {
	return (float)(degrees / 180 * PI);
}

float Utils::degreeToRadians(float degrees) {
	return degrees / 180 * PI;
}

void Utils::drawCube(float length, float width, float height) {
	Utils::drawSolidCube(length, width, height);
}

void Utils::drawSolidCube(float length/*x*/, float height/*y*/, float width/*z*/) {
	glBegin(GL_QUADS);
	glVertex3f(length / 2.0f, height / 2.0f, -width / 2.0f);
	glVertex3f(-length / 2.0f, height / 2.0f, -width / 2.0f);
	glVertex3f(-length / 2.0f, height / 2.0f, width / 2.0f);
	glVertex3f(length / 2.0f, height / 2.0f, width / 2.0f);

	glVertex3f(length / 2.0f, -height / 2.0f, width / 2.0f);
	glVertex3f(-length / 2.0f, -height / 2.0f, width / 2.0f);
	glVertex3f(-length / 2.0f, -height / 2.0f, -width / 2.0f);
	glVertex3f(length / 2.0f, -height / 2.0f, -width / 2.0f);

	glVertex3f(length / 2.0f, height / 2.0f, width / 2.0f);
	glVertex3f(-length / 2.0f, height / 2.0f, width / 2.0f);
	glVertex3f(-length / 2.0f, -height / 2.0f, width / 2.0f);
	glVertex3f(length / 2.0f, -height / 2.0f, -width / 2.0f);

	glVertex3f(length / 2.0f, -height / 2.0f, -width / 2.0f);
	glVertex3f(-length / 2.0f, -height / 2.0f, -width / 2.0f);
	glVertex3f(-length / 2.0f, height / 2.0f, -width / 2.0f);
	glVertex3f(length / 2.0f, height / 2.0f, -width / 2.0f);

	glVertex3f(-length / 2.0f, height / 2.0f, width / 2.0f);
	glVertex3f(-length / 2.0f, height / 2.0f, -width / 2.0f);
	glVertex3f(-length / 2.0f, -height / 2.0f, -width / 2.0f);
	glVertex3f(-length / 2.0f, -height / 2.0f, width / 2.0f);

	glVertex3f(length / 2.0f, height / 2.0f, -width / 2.0f);
	glVertex3f(length / 2.0f, height / 2.0f, width / 2.0f);
	glVertex3f(length / 2.0f, -height / 2.0f, width / 2.0f);
	glVertex3f(length / 2.0f, -height / 2.0f, -width / 2.0f);
	glEnd();
}

void Utils::drawSphere(float radius, float slices, float stacks) {
	glutSolidSphere(radius, slices, stacks);
}

float Utils::abs(float a) {
	return (a > 0) ? a : -a;
}