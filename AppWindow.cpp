#include "AppWindow.h"

int AppWindow::WIDTH;
int AppWindow::HEIGHT;
int AppWindow::TOP;
int AppWindow::LEFT;
float AppWindow::ASPECT;
float AppWindow::WORLD_FRONT_HEIGHT;
float AppWindow::WORLD_FRONT_WIDTH;
float AppWindow::WORLD_BACK_HEIGHT;
float AppWindow::WORLD_BACK_WIDTH;

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::init()
{
	AppWindow::WIDTH = 640;
	AppWindow::HEIGHT = 480;
	AppWindow::TOP = 0;
	AppWindow::LEFT = 0;
	AppWindow::WORLD_FRONT_HEIGHT = 480;
	AppWindow::WORLD_FRONT_WIDTH = 640;
	AppWindow::WORLD_BACK_HEIGHT = 480;
	AppWindow::WORLD_BACK_WIDTH = 640;
	AppWindow::ASPECT = 0.0;
}