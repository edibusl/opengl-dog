#include "Scene.h"



/*
We can't bind GL callbacks to "this", so this is a solution using a 
binding to regular C functions that wrap call to the instance's functions
*/
Scene* g_CurrentInstance;
extern "C"
void drawCallback()
{
	g_CurrentInstance->draw();
}
void reshapeCallback(int width, int height)
{
	g_CurrentInstance->reshape(width, height);
}
void onKeyPressCallback(unsigned char key, int x, int y)
{
	g_CurrentInstance->onKeyPress(key, x, y);
}
void onSpecialKeyPressCallback(int key, int x, int y)
{
	g_CurrentInstance->onSpecialKeyPress(key, x, y);
}


int Scene::ROOM_SIZE = 120;
int Scene::DOG_SIZE = 20;

Scene::Scene(int argc, char** argv)
{
	//Init all classes
	Camera::init();
	AppWindow::init();

	glutInit(&argc, argv);
	init();

	m_dog = new Dog(Scene::DOG_SIZE);
	m_dog->setPosition(10, 10, 10);
	m_dog->y_pos = m_dog->legs[0].UPPER_LEN + m_dog->legs[0].LOWER_LEN + m_dog->BODY_HEIGHT / 2.0f;

	m_room = new Room(Scene::ROOM_SIZE);

	::g_CurrentInstance = this;
	glutDisplayFunc(::drawCallback);
	glutReshapeFunc(::reshapeCallback);
	glutKeyboardFunc(::onKeyPressCallback);
	glutSpecialFunc(::onSpecialKeyPressCallback);
	glutMainLoop();
}


void Scene::init() {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	AppWindow::WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	AppWindow::HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	AppWindow::ASPECT = (float)AppWindow::WIDTH / AppWindow::HEIGHT;
	glutInitWindowSize(AppWindow::WIDTH, AppWindow::HEIGHT);
	AppWindow::TOP = 0;
	AppWindow::LEFT = 0;
	AppWindow::WORLD_FRONT_HEIGHT = 2 * (tan(Utils::radians(Camera::ANGLE / 2)))*(Camera::Z_NEAR);
	AppWindow::WORLD_FRONT_WIDTH = AppWindow::WORLD_FRONT_HEIGHT*AppWindow::ASPECT;
	AppWindow::WORLD_BACK_HEIGHT = 2 * (tan(Utils::radians(Camera::ANGLE / 2)))*(Camera::Z_FAR);
	AppWindow::WORLD_BACK_WIDTH = AppWindow::WORLD_BACK_HEIGHT*AppWindow::ASPECT;
	glutInitWindowPosition(AppWindow::TOP, AppWindow::LEFT);
	glutCreateWindow("Maman 17 - Edi Buslovich");

	//TODO - Aply texture
	//glDepthFunc(GL_LESS);
	//glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
	//glEnable(GL_DEPTH_TEST);
	//InitTexture();
}

void Scene::draw() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Set perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	float aspect = (float)w / h;
	gluPerspective(Camera::ANGLE, aspect, Camera::Z_NEAR, Camera::Z_FAR);

	//Set camera position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Camera::lookAt();


	//Set ambient light
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat globalAmbient[] = { 0.9, 0.9, 0.9, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);*/

	//Spot light
	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHT0);

	this->drawCoordinateArrows();


	glPushMatrix();
	glTranslatef(-Scene::ROOM_SIZE / 2, 0, -Scene::ROOM_SIZE / 2);
	m_room->draw();
	glPopMatrix();

	m_dog->draw();


	glutSwapBuffers();
}

void Scene::drawCoordinateArrows() {
	//Black color
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glEnd();


	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glEnd();


	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();

	Utils::drawText(12.0, 0.0, 0.0, "x");
	Utils::drawText(0.0, 12.0, 0.0, "y");
	Utils::drawText(0.0, 0.0, 12.0, "z");
}

void Scene::reshape(int width, int height) {							/*Preventing distortion due to rescaling*/
	AppWindow::WIDTH = width;
	AppWindow::HEIGHT = height;
	AppWindow::ASPECT = (float)AppWindow::WIDTH / AppWindow::HEIGHT;
	AppWindow::WORLD_FRONT_HEIGHT = 2 * (tan(Utils::radians(Camera::ANGLE / 2)))*(Camera::Z_NEAR);
	AppWindow::WORLD_FRONT_WIDTH = AppWindow::WORLD_FRONT_HEIGHT*AppWindow::ASPECT;
	AppWindow::WORLD_BACK_HEIGHT = 2 * (tan(Utils::radians(Camera::ANGLE / 2)))*(Camera::Z_FAR);
	AppWindow::WORLD_BACK_WIDTH = AppWindow::WORLD_BACK_HEIGHT*AppWindow::ASPECT;
	glViewport(0, 0, AppWindow::WIDTH, AppWindow::HEIGHT);
}

void Scene::onKeyPress(unsigned char key, int x, int y) {
	static int w_press_cnt = 0;
	switch (key) {
	case '6':
	{
		Camera::rotateLookingPoint(1, 0, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case '4':
	{
		Camera::rotateLookingPoint(-1, 0, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case '8':
	{
		Camera::rotateLookingPoint(0, 1, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case '2':
	{
		Camera::rotateLookingPoint(0, -1, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	}
}

void Scene::onSpecialKeyPress(unsigned char key, int x, int y) {
	static int w_press_cnt = 0;
	switch (key) {
	case GLUT_KEY_RIGHT:
	{
		Camera::rotatePosition(1, 0, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_LEFT:
	{
		Camera::rotatePosition(-1, 0, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_UP:
	{
		Camera::rotatePosition(0, 1, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_DOWN:
	{
		Camera::rotatePosition(0, -1, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_PAGE_UP:
	{
		Camera::rotatePosition(0, 0, -1);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_PAGE_DOWN:
	{
		Camera::rotatePosition(0, 0, 1);
		Camera::lookAt();
		this->draw();

		break;
	}
	}
}