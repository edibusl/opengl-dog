#include "Lamp.h"

Lamp::Lamp()
{
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
}

void Lamp::draw(int x, int y, int z)
{
	GLfloat colorWhite[] = { 0.5, 0.5, 0.5, 1.0 };
	
	GLfloat lightPosition1[] = { x, y - 15, z, 1 };
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
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Translate
	glPushMatrix();
	glTranslatef(x, y, z);
	
	//Set global ambient light
	glEnable(GL_LIGHTING);
	/*GLfloat globalAmbient[] = { 0.9, 0.9, 0.9, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);*/

	//Spot light
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
	GLfloat whiteColor[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat lightPosition[] = { x, y - 15, z, 0 };
	GLfloat lightDirection[] = { 100, 100, 100 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.5);

	//Lamp's cable
	glPushMatrix();
	glColor3fv(Color::Black);
	glRotatef(90, 1, 0, 0);
	Utils::drawCylinder(0.5, 15);
	glPopMatrix();
	
	//Round lamp
	/*glPushMatrix();
	glTranslatef(0, -15, 0);
	glColor3fv(Color::Yellow);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color::Yellow);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Color::Yellow);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Color::Yellow);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.0);
	
	Utils::drawSphere(4, 32, 32, FaceType::SOLID);
	glPopAttrib();
	glPopMatrix();*/


	//Remove lamp position translation
	glPopMatrix();
}