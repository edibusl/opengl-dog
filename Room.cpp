#include "Room.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



int Room::WALL_THICKNESS = 5;

Room::Room(int width, int height)
{
	this->m_width = width;
	this->m_height = height;

	GLuint textures[3];
	glGenTextures(3, textures);
	this->m_textureWall = textures[0];
	this->m_textureFloor = textures[1];
	this->m_textureCeiling = textures[2];
	Utils::loadTexture(this->m_textureWall, "textures\\wall3.jpg");
	Utils::loadTexture(this->m_textureFloor, "textures\\floor1.jpg");
	Utils::loadTexture(this->m_textureCeiling, "textures\\ceiling2.jpg");
}


void Room::draw() {
	glEnable(GL_TEXTURE_2D);
	
	//Back wall
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, this->m_textureWall);
	this->drawWall();


	//Front wall
	glTranslatef(0, 0, this->m_width);
	this->drawWall();
	glPopMatrix();

	//Left wall
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	this->drawWall();
	glPopMatrix();

	//Right Wall
	glPushMatrix();
	glTranslatef(this->m_width, 0, 0);
	glRotatef(-90, 0, 1, 0);
	this->drawWall();
	glPopMatrix();

	//Floor
	glBindTexture(GL_TEXTURE_2D, this->m_textureFloor);
	glPushMatrix();
	this->drawHorizontalWall();
	glPopMatrix();

	//Ceiling
	glBindTexture(GL_TEXTURE_2D, this->m_textureCeiling);
	glPushMatrix();
	glTranslatef(0, this->m_height, 0);
	this->drawHorizontalWall();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Room::drawWall()
{
	glBegin(GL_POLYGON);

	glColor3fv(Color::White);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::White);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::Purple);
	glNormal3f(1, 0, 0);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0, this->m_height, 0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(this->m_width, this->m_height, 0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(this->m_width, 0, 0);

	glEnd();
}

void Room::drawHorizontalWall()
{
	glBegin(GL_POLYGON);

	
	glColor3fv(Color::White);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Color::White);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Color::Yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::Purple);
	glMaterialf(GL_FRONT, GL_SHININESS, 120.0);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0, 0, 0);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(this->m_width, 0, 0);

	glNormal3f(0, 1, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(this->m_width, 0, this->m_width);

	glNormal3f(0, 1, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0, 0, this->m_width);

	//glDisable(GL_BLEND);
	//glDisable(GL_COLOR_MATERIAL);


	glPopAttrib();

	glEnd();
}