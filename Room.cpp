#include "Room.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



int Room::WALL_THICKNESS = 5;

Room::Room(int size)
{
	this->m_size = size;

	GLuint textures[3];
	glGenTextures(3, textures);
	this->m_textureWall = textures[0];
	this->m_textureFloor = textures[1];
	this->m_textureCeiling = textures[2];
	Utils::loadTexture(this->m_textureWall, "textures\\warm_wall.jpg");
	Utils::loadTexture(this->m_textureFloor, "textures\\marble.jpg");
	Utils::loadTexture(this->m_textureCeiling, "textures\\ceiling2.jpg");
}


void Room::draw() {
	glEnable(GL_TEXTURE_2D);
	
	//Back wall
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, this->m_textureWall);
	glColor3fv(Color::White);
	this->drawWall();


	//Front wall
	glTranslatef(0, 0, this->m_size);
	this->drawWall();
	glPopMatrix();

	//Left wall
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	this->drawWall();
	glPopMatrix();

	//Right Wall
	glPushMatrix();
	glTranslatef(this->m_size, 0, 0);
	glRotatef(-90, 0, 1, 0);
	this->drawWall();
	glPopMatrix();

	//Floor
	glBindTexture(GL_TEXTURE_2D, this->m_textureFloor);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	this->drawWall();
	glPopMatrix();

	//Ceiling
	glBindTexture(GL_TEXTURE_2D, this->m_textureCeiling);
	glPushMatrix();
	glTranslatef(0, this->m_size, 0);
	glRotatef(90, 1, 0, 0);
	this->drawWall();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Room::drawWall()
{
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0, this->m_size, 0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(this->m_size, this->m_size, 0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(this->m_size, 0, 0);

	glEnd();
}