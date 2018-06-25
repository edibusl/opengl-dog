#include "Utils.h"

#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

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

void Utils::drawCube(float length, float width, float height, FaceType faceType) {
	if (faceType == FaceType::SOLID) {
		Utils::drawSolidCube(length, width, height);
	}
	else {
		Utils::drawWireCube(length, width, height);
	}
}

void Utils::drawSolidCube(float length/*x*/, float height/*y*/, float width/*z*/) {
	glBegin(GL_QUADS);
	
	
	//static float front_mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	//static float front_mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	//static float back_mat_diffuse[] = { 1.0, 1.0, 0.2, 1.0 };
	//static float back_mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, front_mat_diffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, front_mat_ambient);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, front_mat_diffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, front_mat_diffuse);

	static float all_colors[] = { 0.2, 0.2, 0.2, 1.0 };
	static float specular_color[] = { 0.8, 0.1, 0.5, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, all_colors);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_color);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120.0);
	
	

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

void Utils::drawWireCube(float length/*x*/, float height/*y*/, float width/*z*/) {
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.50000*length, -0.50000*height, 0.50000*width);
	glVertex3f(0.50000*length, -0.50000*height, 0.50000*width);
	glVertex3f(0.50000*length, 0.50000*height, 0.50000*width);
	glVertex3f(-0.50000*length, 0.50000*height, 0.50000*width);
	glVertex3f(-0.50000*length, -0.50000*height, 0.50000*width);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.50000*length, 0.50000*height, 0.50000*width);
	glVertex3f(-0.50000*length, 0.50000*height, -0.50000*width);
	glVertex3f(0.50000*length, 0.50000*height, -0.50000*width);
	glVertex3f(0.50000*length, 0.50000*height, 0.50000*width);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.50000*length, 0.50000*height, -0.50000*width);
	glVertex3f(-0.50000*length, -0.50000*height, -0.50000*width);
	glVertex3f(0.50000*length, -0.50000*height, -0.50000*width);
	glVertex3f(0.50000*length, 0.50000*height, -0.50000*width);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.50000*length, -0.50000*height, -0.50000*width);
	glVertex3f(0.50000*length, -0.50000*height, -0.50000*width);
	glVertex3f(0.50000*length, -0.50000*height, 0.50000*width);
	glVertex3f(-0.50000*length, -0.50000*height, 0.50000*width);
	glVertex3f(-0.50000*length, -0.50000*height, -0.50000*width);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.500000*length, -0.50000*height, 0.50000*width);
	glVertex3f(0.50000*length, -0.50000*height, -0.50000*width);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.50000*length, -0.50000*height, -0.50000*width);
	glVertex3f(-0.50000*length, -0.50000*height, 0.50000*width);
	glEnd();

}

void Utils::drawSphere(float radius, float slices, float stacks, FaceType faceType) {
	if (faceType == FaceType::SOLID) {
		glutSolidSphere(radius, slices, stacks);
	}
	else {
		glutWireSphere(radius, slices, stacks);
	}
}

float Utils::abs(float a) {
	return (a > 0) ? a : -a;
}

void Utils::drawText(GLfloat x, GLfloat y, GLfloat z, string text)
{
	//Set position
	glRasterPos3f(x, y, z);
	for (unsigned int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]); //Draw one letter according to the font
	}
}

void Utils::drawEllipsoid(float fA, float fB, float fC, unsigned int uiSlices, unsigned int uiStacks)
{
	float tStep = (PI) / (float)uiSlices;
	float sStep = (PI) / (float)uiStacks;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (float t = -PI / 2; t <= (PI / 2) + .0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (float s = -PI; s <= PI + .0001; s += sStep)
		{
			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
			glVertex3f(fA * cos(t + tStep) * cos(s), fB * cos(t + tStep) * sin(s), fC * sin(t + tStep));
		}
		glEnd();
	}
}

void Utils::loadTexture(GLuint texture, const char* filePath)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		//Failed to load
	}
	stbi_image_free(data);
}

void Utils::getIdentityMatrix()
{
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
}

void Utils::drawCylinder(GLdouble baseRadius, GLdouble length)
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, baseRadius, baseRadius, length, 32, 32);
}

void Utils::drawCone(GLdouble baseRadius, GLdouble length)
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0, baseRadius, length, 32, 32);
}