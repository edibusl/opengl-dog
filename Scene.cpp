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
void menuCallback(int value)
{
	g_CurrentInstance->onMenuClick(value);
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

int Scene::ROOM_WIDTH = 160;
int Scene::ROOM_HEIGHT = 120;
int Scene::DOG_SIZE = 20;
string Scene::WINDOW_TITLE = "Maman 17 - Edi Buslovich";

Scene::Scene(int argc, char** argv)
{
	m_lightGlobalIntensity = 0;
	m_curKeysControl = KeysControl::NONE;

	//Init classes
	Camera::init();
	AppWindow::init();

	glutInit(&argc, argv);
	
	//Init viewing window
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
	glutCreateWindow(WINDOW_TITLE.c_str());

	//Enable depth testing when rendering objects (z-buffer)
	glEnable(GL_DEPTH_TEST);

	//Set perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	float aspect = (float)w / h;
	gluPerspective(Camera::ANGLE, aspect, Camera::Z_NEAR, Camera::Z_FAR);

	//Init vars
	m_bShowCoordinateArrows = false;
	m_bDogEyesView = false;

	//Create dog
	m_dog = new Dog(Scene::DOG_SIZE);
	m_dog->setPosition(-10, m_dog->m_legs[0].m_upperLen + m_dog->m_legs[0].m_lowerLen + m_dog->m_bodyHeight / 2.0f - 2, 10);

	//Create room, lamp and furniture
	m_room = new Room(Scene::ROOM_WIDTH, Scene::ROOM_HEIGHT);
	m_lamp = new Lamp();
	m_lightPositionX = -20;
	m_lightPositionY = Scene::ROOM_HEIGHT;
	m_lightPositionZ = -20;
	m_furniture = new Furniture(25, 0, -40);

	//Set glut callbacks
	::g_CurrentInstance = this;
	glutDisplayFunc(::drawCallback);
	glutReshapeFunc(::reshapeCallback);
	glutKeyboardFunc(::onKeyPressCallback);
	glutSpecialFunc(::onSpecialKeyPressCallback);

	Utils::maximizeWindow(WINDOW_TITLE);

	glutMainLoop();
}

void Scene::draw() {
	//Reset colors and model view matrix
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Set camera position
	if (m_bDogEyesView) {
		GLfloat* eyesPos = m_dog->getEyesPosition();
		GLfloat* eyesLookat = m_dog->getEyesLookAt();
		Camera::lookAt(eyesPos[0], eyesPos[1], eyesPos[2], eyesLookat[0], eyesLookat[1], eyesLookat[2]);
	}
	else
	{
		Camera::lookAt();
	}
	
	//Save the view matrix to be used later for eye position calculation
	m_dog->saveViewMatrix();

	//Lighting
	this->initLight();

	//Draw lamp and set its light
	m_lamp->draw(m_lightPositionX, m_lightPositionY, m_lightPositionZ);
	m_lamp->setLighting();

	//Draw room
	glPushMatrix();
	glTranslatef(-Scene::ROOM_WIDTH / 2, 0, -Scene::ROOM_WIDTH / 2);
	m_room->draw();
	glPopMatrix();

	//Draw dog
	m_dog->draw();

	//Draw furniture
	m_furniture->draw();

	//Draw debugging coordinates
	this->drawCoordinateArrows();

	//Init menu while drawing since the text of the menus may change
	this->initMenu();

	//Draw text with instructions for controlling
	this->drawKeysControlText();
	
	glutSwapBuffers();
}

void Scene::initLight()
{
	//General lighting settings
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH); //Gourad

	//Global ambient
	//float globalAmbient[] = { 0.8, 0.8, 0.8, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	glEnable(GL_LIGHT0);
	this->setLightGlobalIntensity(0);
}

void Scene::setLightGlobalIntensity(float diff)
{
	m_lightGlobalIntensity += diff;
	float intensity[] = { 0.8 + m_lightGlobalIntensity, 0.8 + m_lightGlobalIntensity, 0.8 + m_lightGlobalIntensity, 1};

	glLightfv(GL_LIGHT0, GL_AMBIENT, intensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, intensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR, intensity);
}

void Scene::drawCoordinateArrows() {
	if (!m_bShowCoordinateArrows) {
		return;
	}

	//Black color
	glColor3fv(Color::Blue);

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

void Scene::reshape(int width, int height) {
	AppWindow::WIDTH = width;
	AppWindow::HEIGHT = height;
	AppWindow::ASPECT = (float)AppWindow::WIDTH / AppWindow::HEIGHT;
	AppWindow::WORLD_FRONT_HEIGHT = 2 * (tan(Utils::radians(Camera::ANGLE / 2))) * (Camera::Z_NEAR);
	AppWindow::WORLD_FRONT_WIDTH = AppWindow::WORLD_FRONT_HEIGHT * AppWindow::ASPECT;
	AppWindow::WORLD_BACK_HEIGHT = 2 * (tan(Utils::radians(Camera::ANGLE / 2))) * (Camera::Z_FAR);
	AppWindow::WORLD_BACK_WIDTH = AppWindow::WORLD_BACK_HEIGHT * AppWindow::ASPECT;
	glViewport(0, 0, AppWindow::WIDTH, AppWindow::HEIGHT);
}

void Scene::initMenu() {
	int camera = glutCreateMenu(::menuCallback);
	glutAddMenuEntry("Control camera position", KeysControl::CAMERA_POSITION);
	glutAddMenuEntry("Control lookat", KeysControl::CAMERA_LOOKAT);
	if (m_bDogEyesView)
	{
		glutAddMenuEntry("Disable dog eyes' view", KeysControl::CAMERA_DOGVIEW);
	}
	else
	{
		glutAddMenuEntry("Dog eyes' view", KeysControl::CAMERA_DOGVIEW);
	}

	int light = glutCreateMenu(::menuCallback);
	glutAddMenuEntry("Control lamp (spotlight) position", KeysControl::SPOTLIGHT_POSITION);
	glutAddMenuEntry("Control lamp (spotlight) direction", KeysControl::SPOTLIGHT_DIRECTION);
	glutAddMenuEntry("Change lamp (spotlight) intensity", KeysControl::SPOTLIGHT_INTENSITY);
	glutAddMenuEntry("Change global light intensity", KeysControl::LIGHT_GLOBAL_INTENSITY);

	int dog = glutCreateMenu(::menuCallback);
	glutAddMenuEntry("Move tail", KeysControl::MOVE_TAIL);
	glutAddMenuEntry("Move head", KeysControl::MOVE_HEAD);

	int debug = glutCreateMenu(::menuCallback);
	if (m_bShowCoordinateArrows) {
		glutAddMenuEntry("Hide coordinate system", KeysControl::SWITCH_COORDINATE_SYSTEM);
	}
	else {
		glutAddMenuEntry("Show coordinate system", KeysControl::SWITCH_COORDINATE_SYSTEM);
	}

	int mainmenu = glutCreateMenu(::menuCallback);
	glutAddSubMenu("Camera", camera);
	glutAddSubMenu("Light", light);
	glutAddSubMenu("Dog", dog);
	glutAddSubMenu("Debugging", debug);
	glutAddMenuEntry("Stop controlling", KeysControl::NONE);
	glutAddMenuEntry("Quit", KeysControl::EXIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Scene::onMenuClick(int value) {
	m_curKeysControl = (KeysControl)value;
	switch (m_curKeysControl)
	{
		case KeysControl::SWITCH_COORDINATE_SYSTEM:
		{
			m_bShowCoordinateArrows = !m_bShowCoordinateArrows;
			break;
		}
		case KeysControl::CAMERA_DOGVIEW:
		{
			m_bDogEyesView = !m_bDogEyesView;
			break;
		}
		case KeysControl::EXIT:
		{
			exit(0);
		}
	}

	glutPostRedisplay();
}

void Scene::drawKeysControlText() {
	switch (m_curKeysControl)
	{
		case KeysControl::NONE:
		{
			Utils::drawTextOnScreen("Right mouse click for options menu.");
			break;
		}
		case KeysControl::CAMERA_POSITION:
		{
			Utils::drawTextOnScreen("Control camera position: ** Use keyboard's left/right keys to control X axis ** Use up/down keys to control Y axis ** Use PageUp/PageDown keys to control Z axis.");
			break;
		}
		case KeysControl::CAMERA_LOOKAT:
		{
			Utils::drawTextOnScreen("Control camera lookat: ** Use keyboard's left/right keys to control X axis ** Use up/down keys to control Y axis ** Use PageUp/PageDown keys to control Z axis.");
			break;
		}
		case KeysControl::CAMERA_DOGVIEW:
		{
			if (m_bDogEyesView) {
				Utils::drawTextOnScreen("Camera is positioned at dog's eyes");
			}

			break;
		}
		case KeysControl::MOVE_TAIL:
		{
			Utils::drawTextOnScreen("Control dog's tail: ** Use keyboard's left/right keys to move tail left and right ** Use up/down keys to move tail up and down.");
			break;
		}
		case KeysControl::MOVE_HEAD:
		{
			Utils::drawTextOnScreen("Control dog's head: ** Use keyboard's left/right keys to move head left and right ** Use up/down keys to move head up and down.");
			break;
		}
		case KeysControl::SPOTLIGHT_POSITION:
		{
			Utils::drawTextOnScreen("Control spotlight position: ** Use keyboard's left/right keys to control X axis ** Use PageUp/PageDown keys to control Z axis.");
			break;
		}
		case KeysControl::SPOTLIGHT_DIRECTION:
		{
			Utils::drawTextOnScreen("Control spotlight direction: ** Use keyboard's left/right keys to control X axis ** Use PageUp/PageDown keys to control Z axis.");
			break;
		}
		case KeysControl::SPOTLIGHT_INTENSITY:
		{
			Utils::drawTextOnScreen("Control spotlight intensity: ** Use keyboard's +/- keys to control intensity.");
			break;
		}
		case KeysControl::LIGHT_GLOBAL_INTENSITY:
		{
			Utils::drawTextOnScreen("Control global light intensity: ** Use keyboard's +/- keys to control intensity.");
			break;
		}
	}
}

void Scene::onKeyPress(unsigned char key, int x, int y) {
	switch (key) {
		case 'p':
		{
			m_curKeysControl = KeysControl::CAMERA_POSITION;
			return;
		}
		case 'e':
		{
			m_curKeysControl = KeysControl::CAMERA_LOOKAT;
			return;
		}
		case 'n':
		{
			m_curKeysControl = KeysControl::SPOTLIGHT_POSITION;
			return;
		}
		case 'm':
		{
			m_curKeysControl = KeysControl::SPOTLIGHT_DIRECTION;
			return;
		}
	}

	switch (m_curKeysControl)
	{
		case KeysControl::LIGHT_GLOBAL_INTENSITY:
			this->handleLightGlobalIntensity(key);
			this->draw();
			return;
		case KeysControl::SPOTLIGHT_INTENSITY:
			this->handleSpotlightIntensity(key);
			this->draw();
			return;
	}
}

void Scene::onSpecialKeyPress(unsigned char key, int x, int y) {
	switch (m_curKeysControl)
	{
		case KeysControl::CAMERA_LOOKAT:
			this->handleCameraLookAt(key);
			break;
		case KeysControl::CAMERA_POSITION:
			this->handleCameraPosition(key);
			break;
		case KeysControl::SPOTLIGHT_DIRECTION:
			this->handleSpotlightDirection(key);
			break;
		case KeysControl::SPOTLIGHT_POSITION:
			this->handleSpotlightPosition(key);
			break;
		case KeysControl::MOVE_TAIL:
			this->handleMoveTail(key);
			break;
		case KeysControl::MOVE_HEAD:
			this->handleMoveHead(key);
			break;
	}
}

void Scene::handleCameraLookAt(unsigned char key)
{
	switch (key) {
		case GLUT_KEY_RIGHT:
		{
			Camera::changeLookingPoint(1, 0, 0);
			Camera::lookAt();
			this->draw();

			break;
		}
		case GLUT_KEY_LEFT:
		{
			Camera::changeLookingPoint(-1, 0, 0);
			Camera::lookAt();
			this->draw();

			break;
		}
		case GLUT_KEY_UP:
		{
			Camera::changeLookingPoint(0, 1, 0);
			Camera::lookAt();
			this->draw();

			break;
		}
		case GLUT_KEY_DOWN:
		{
			Camera::changeLookingPoint(0, -1, 0);
			Camera::lookAt();
			this->draw();

			break;
		}
	}
}

void Scene::handleCameraPosition(unsigned char key)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
	{
		Camera::changePosition(1, 0, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_LEFT:
	{
		Camera::changePosition(-1, 0, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_UP:
	{
		Camera::changePosition(0, 1, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_DOWN:
	{
		Camera::changePosition(0, -1, 0);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_PAGE_UP:
	{
		Camera::changePosition(0, 0, -1);
		Camera::lookAt();
		this->draw();

		break;
	}
	case GLUT_KEY_PAGE_DOWN:
	{
		Camera::changePosition(0, 0, 1);
		Camera::lookAt();
		this->draw();

		break;
	}
	}
}

void Scene::handleSpotlightPosition(unsigned char key)
{
	switch (key) {
		case GLUT_KEY_RIGHT:
		{
			this->setLampPosition(1, 0, 0);
			break;
		}
		case GLUT_KEY_LEFT:
		{
			this->setLampPosition(-1, 0, 0);
			break;
		}
		case GLUT_KEY_PAGE_UP:
		{
			this->setLampPosition(0, 0, -1);
			break;
		}
		case GLUT_KEY_PAGE_DOWN:
		{
			this->setLampPosition(0, 0, 1);
			break;
		}
	}

	this->draw();
}


void Scene::handleSpotlightDirection(unsigned char key)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
	{
		m_lamp->setLightDirection(1, 0);
		break;
	}
	case GLUT_KEY_LEFT:
	{
		m_lamp->setLightDirection(-1, 0);
		break;
	}
	case GLUT_KEY_PAGE_UP:
	{
		m_lamp->setLightDirection(0, 1);
		break;
	}
	case GLUT_KEY_PAGE_DOWN:
	{
		m_lamp->setLightDirection(0, -1);
		break;
	}
	}

	this->draw();
}


void Scene::handleMoveTail(unsigned char key)
{
	switch (key) {
		case GLUT_KEY_RIGHT:
		{
			m_dog->setTailAngle(4, 0);
			break;
		}
		case GLUT_KEY_LEFT:
		{
			m_dog->setTailAngle(-4, 0);
			break;
		}
		case GLUT_KEY_UP:
		{
			m_dog->setTailAngle(0, -2);
			break;
		}
		case GLUT_KEY_DOWN:
		{
			m_dog->setTailAngle(0, 2);
			break;
		}
	}

	this->draw();
}

void Scene::handleMoveHead(unsigned char key)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
	{
		m_dog->setNeckAngle(-4, 0);
		break;
	}
	case GLUT_KEY_LEFT:
	{
		m_dog->setNeckAngle(4, 0);
		break;
	}
	case GLUT_KEY_UP:
	{
		m_dog->setNeckAngle(0, 4);
		break;
	}
	case GLUT_KEY_DOWN:
	{
		m_dog->setNeckAngle(0, -4);
		break;
	}
	}

	this->draw();
}

void Scene::handleLightGlobalIntensity(unsigned char key)
{
	switch (key) {
		case '+':
		{
			this->setLightGlobalIntensity(0.05);
			break;
		}
		case '-':
		{
			this->setLightGlobalIntensity(-0.05);
			break;
		}
	}

	this->draw();
}

void Scene::handleSpotlightIntensity(unsigned char key)
{
	switch (key) {
	case '+':
	{
		m_lamp->setIntensity(0.05);
		break;
	}
	case '-':
	{
		m_lamp->setIntensity(-0.05);
		break;
	}
	}

	this->draw();
}

void Scene::setLampPosition(int x, int y, int z)
{
	m_lightPositionX += x;
	m_lightPositionY += y;
	m_lightPositionZ += z;
}