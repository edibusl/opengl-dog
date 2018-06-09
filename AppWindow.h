#pragma once
class AppWindow
{
public:
	static int WIDTH;
	static int HEIGHT;
	static int TOP;
	static int LEFT;
	static float ASPECT;
	static float WORLD_FRONT_HEIGHT;
	static float WORLD_FRONT_WIDTH;
	static float WORLD_BACK_HEIGHT;
	static float WORLD_BACK_WIDTH;

public:
	static void init();

private:
	AppWindow();
	~AppWindow();
};