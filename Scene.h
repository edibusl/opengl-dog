#pragma once
#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <string>
#include <iostream>

#include "consts.h"
#include "Utils.h"
#include "Camera.h"
#include "AppWindow.h"
#include "Dog.h"
#include "Room.h"
#include "Lamp.h"

using namespace std;


class Scene
{
private:
	static int ROOM_WIDTH;
	static int ROOM_HEIGHT;
	static int DOG_SIZE;

	Dog* m_dog;
	Room* m_room;
	Lamp* m_lamp;

public:
	Scene(int argc, char** argv);

	void init();
	void draw();

	void drawCoordinateArrows();

	void reshape(int width, int height);
	void onKeyPress(unsigned char key, int x, int y);
	void onSpecialKeyPress(unsigned char key, int x, int y);
};

