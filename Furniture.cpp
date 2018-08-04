#include "Furniture.h"

const GLfloat Furniture::TableLegSizeX = 2;
const GLfloat Furniture::TableLegSizeY = 20;
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
	Utils::drawCube(TableLegSizeX, TableLegSizeY, TableLegSizeZ, FaceType::SOLID);
	glTranslatef(TableSurfaceSize, 0, 0);
	Utils::drawCube(TableLegSizeX, TableLegSizeY, TableLegSizeZ, FaceType::SOLID);
	glTranslatef(0, 0, TableSurfaceSize);
	Utils::drawCube(TableLegSizeX, TableLegSizeY, TableLegSizeZ, FaceType::SOLID);
	glTranslatef(-TableSurfaceSize, 0, 0);
	Utils::drawCube(TableLegSizeX, TableLegSizeY, TableLegSizeZ, FaceType::SOLID);
	glTranslatef(0, 0, -TableSurfaceSize);

	//Table surface
	glPushMatrix();
	glTranslatef(TableSurfaceSize / 2, (TableLegSizeY / 2) - (TableSurfaceThickness / 2), TableSurfaceSize / 2);
	glRotatef(90, 0, 1, 0);
	Utils::drawCube(TableSurfaceSize, TableSurfaceThickness, TableSurfaceSize, FaceType::SOLID);
	glPopMatrix();

	//Teapot
	glPushMatrix();
	glTranslatef(TableSurfaceSize / 2, (TableLegSizeY / 2) + TableSurfaceThickness, TableSurfaceSize / 2);
	glutSolidTeapot(TeapotSize);
	glPopMatrix();

	//Disable initial position translation
	glPopMatrix();
}