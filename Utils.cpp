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
	
	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, -height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, -height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, -height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, -height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, -height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, -height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, -height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, -height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, -height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(-length / 2.0f, -height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, height / 2.0f, -width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
	glVertex3f(length / 2.0f, -height / 2.0f, width / 2.0f);

	glNormal3f(0, 1.0, 0.0);
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

void Utils::drawTextOnScreen(string text)
{
	//Assume we are in MODEL_VIEW already	
	//Save and reset the model view matrix
	glPushMatrix();
	glLoadIdentity();

	//Save and reset the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	//Get the viewport screen dimensions and switch to 2D orthographic projection mode
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluOrtho2D(0, viewport[2], 0, viewport[3]);

	//Draw the text at the bottom left of the viewport
	glColor3fv(Color::Black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Color::Black);
	glRasterPos2f(50, 50);
	for (unsigned int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]); //Draw one letter according to the font
	}

	//Reset to previously saved projection (perspective)
	glPopMatrix();

	//Reset to previously saved model view matrix
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Utils::drawEllipsoid(float fA, float fB, float fC, unsigned int uiSlices, unsigned int uiStacks)
{
	float tStep = (PI) / (float)uiSlices;
	float sStep = (PI) / (float)uiStacks;
	for (float t = -PI / 2; t <= (PI / 2) + .0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (float s = -PI; s <= PI + .0001; s += sStep)
		{
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));

			glNormal3f(1.0, 0.0, 0.0);
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

void Utils::maximizeWindow(string windowTitle)
{
	HWND win_handle = FindWindow(0, windowTitle.c_str());
	if (!win_handle)
	{
		printf("!!! Failed FindWindow\n");
	}

	SetWindowLong(win_handle, GWL_STYLE, (GetWindowLong(win_handle, GWL_STYLE) | WS_MAXIMIZE));
	ShowWindowAsync(win_handle, SW_SHOWMAXIMIZED);
}

float* Utils::getModelViewMatrix()
{
	float* mat = new float[16];
	memset(mat, 0, 16 * sizeof(*mat));
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);

	return mat;
}

GLfloat* Utils::multMatrixVector4f(float* matrix, float* vector)
{
	//Multiple a column based array that holds a matrix by a vector

	GLfloat* pos = new GLfloat[4];
	memset(pos, 0, 4 * sizeof(*pos));
	
	for (int i = 0; i < 4; i++)
	{
		pos[0] += (matrix[0 + 4*i] * vector[i % 4]);
		pos[1] += (matrix[1 + 4 * i] * vector[i % 4]);
		pos[2] += (matrix[2 + 4 * i] * vector[i % 4]);
		pos[3] += (matrix[3 + 4 * i] * vector[i % 4]);
	}

	return pos;
}

GLfloat* Utils::multMatrices4f(float* matrix1, float* matrix2)
{
	GLfloat* result = new GLfloat[16];
	memset(result, 0, 16 * sizeof(*result));

	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			result[j * 4 + i] = 0;

			for (k = 0; k < 4; k++) {
				result[j * 4 + i] += matrix1[k * 4 + i] * matrix2[j * 4 + k];
			}
		}
	}


	return result;
}

bool Utils::gluInvertMatrix(const float m[16], float invOut[16])
{
	float inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;

	return true;
}