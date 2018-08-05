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
#include "Furniture.h"

using namespace std;

enum KeysControl {
	NONE = -1,
	EXIT = 0,
	CAMERA_POSITION = 1,
	CAMERA_LOOKAT = 2,	
	CAMERA_DOGVIEW = 3,
	LIGHT_DIRECTION = 4,
	LIGHT_GLOBAL_INTENSITY = 5,
	MOVE_TAIL = 6,
	MOVE_HEAD = 7,
	SWITCH_COORDINATE_SYSTEM = 8,
	LAMP_DIRECTION = 20,
	SPOTLIGHT_POSITION = 21,
	SPOTLIGHT_DIRECTION = 22
};

class Scene
{
private:
	static int ROOM_WIDTH;
	static int ROOM_HEIGHT;
	static int DOG_SIZE;
	static string WINDOW_TITLE;

	Dog* m_dog;
	Room* m_room;
	Lamp* m_lamp;
	Furniture* m_furniture;

	KeysControl m_curKeysControl;

	int m_LightPositionX;
	int m_LightPositionY;
	int m_LightPositionZ;
	float m_lightGlobalIntensity;
	bool m_bLightDiffuse;
	bool m_bLightSpecular;
	bool m_bShowCoordinateArrows;
	bool m_bDogEyesView;

public:
	Scene(int argc, char** argv);

	void init();
	void draw();

	void drawCoordinateArrows();

	void reshape(int width, int height);
	void onKeyPress(unsigned char key, int x, int y);
	void onSpecialKeyPress(unsigned char key, int x, int y);
	void onMenuClick(int value);

private:
	void initMenu();
	void initLight();
	void drawKeysControlText();
	void handleCameraLookAt(unsigned char key);
	void handleCameraPosition(unsigned char key);
	void handleLampDirection(unsigned char key);
	void handleLightPosition(unsigned char key);
	void handleMoveTail(unsigned char key);
	void handleMoveHead(unsigned char key);
	void handleSpotlightPosition(unsigned char key);
	void handleSpotlightDirection(unsigned char key);
	void lightRotatePosition(int x, int y, int z);
	void handleLightGlobalIntensity(unsigned char key);
	void setLightGlobalIntensity(float diff);
};

