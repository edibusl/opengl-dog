#include "Furniture.h"

const GLfloat Furniture::TableLegSizeX = 2;
const GLfloat Furniture::TableLegSizeY = 15;
const GLfloat Furniture::TableLegSizeZ = 2;
const GLfloat Furniture::TableSurfaceSize = 20;
const GLfloat Furniture::TableSurfaceThickness = 3;
const GLfloat Furniture::TeapotSize  = 5;

Furniture::Furniture(int initialPosX, int initialPosY, int initialPosZ)
{
	this->m_PosX = initialPosX;
	this->m_PosY = initialPosY;
	this->m_PosZ = initialPosZ;
}


Furniture::~Furniture()
{
}

void Furniture::draw() {
	//Translate furniture's initial position
	glPushMatrix();
	glTranslatef(m_PosX, m_PosY + (Furniture::TableLegSizeY / 2), m_PosZ);

	//Table legs
	glColor3fv(Color::TableLeg);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::TableLeg);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::TableLeg);

	Utils::drawCube(TableLegSizeX, TableLegSizeY, TableLegSizeZ);
	glTranslatef(TableSurfaceSize, 0, 0);
	Utils::drawCube(TableLegSizeX, TableLegSizeY, TableLegSizeZ);
	glTranslatef(0, 0, TableSurfaceSize);
	Utils::drawCube(TableLegSizeX, TableLegSizeY, TableLegSizeZ);
	glTranslatef(-TableSurfaceSize, 0, 0);
	Utils::drawCube(TableLegSizeX, TableLegSizeY, TableLegSizeZ);
	glTranslatef(0, 0, -TableSurfaceSize);

	//Table surface
	glColor3fv(Color::TableSurface);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::TableSurface);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::TableSurface);

	glPushMatrix();
	glTranslatef(TableSurfaceSize / 2, (TableLegSizeY / 2) - (TableSurfaceThickness / 2), TableSurfaceSize / 2);
	glRotatef(90, 0, 1, 0);
	Utils::drawCube(TableSurfaceSize, TableSurfaceThickness, TableSurfaceSize);
	glPopMatrix();

	//Teapot
	glColor3fv(Color::TeapotAmbient);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::TeapotAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::TeapotDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::TeapotSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.2 * 128);

	glPushMatrix();
	glTranslatef(TableSurfaceSize / 2, (TableLegSizeY / 2) + TableSurfaceThickness, TableSurfaceSize / 2);
	glutSolidTeapot(TeapotSize);
	glPopMatrix();

	//Disable initial position translation
	glPopMatrix();
}