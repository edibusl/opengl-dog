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
	m_curKeysControl = KeysControl::NONE;

	//Init all classes
	Camera::init();
	AppWindow::init();

	glutInit(&argc, argv);
	init();

	m_dog = new Dog(Scene::DOG_SIZE);
	
	//TODO - Check dog's y position (it's for some reason above floor)
	m_dog->setPosition(-10, m_dog->legs[0].UPPER_LEN + m_dog->legs[0].LOWER_LEN + m_dog->BODY_HEIGHT / 2.0f, 10);

	m_room = new Room(Scene::ROOM_WIDTH, Scene::ROOM_HEIGHT);
	m_lamp = new Lamp();
	m_furniture = new Furniture(25, 0, -40);

	::g_CurrentInstance = this;
	glutDisplayFunc(::drawCallback);
	glutReshapeFunc(::reshapeCallback);
	glutKeyboardFunc(::onKeyPressCallback);
	glutSpecialFunc(::onSpecialKeyPressCallback);

	Utils::maximizeWindow(WINDOW_TITLE);

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
	glutCreateWindow(WINDOW_TITLE.c_str());

	//Enable depth testing when rendering objects
	glEnable(GL_DEPTH_TEST);
	
	
	//Set perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	float aspect = (float)w / h;
	gluPerspective(Camera::ANGLE, aspect, Camera::Z_NEAR, Camera::Z_FAR);


	//Coordinate system arrows
	m_bShowCoordinateArrows = false;

	//Dog eye view
	m_bDogEyesView = false;

	//Lighting
	static float globalAmbient[] = { 0.8, 0.8, 0.8, 1.0 };
	static float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	m_LightPositionX = 0;
	m_LightPositionY = 40;
	m_LightPositionZ = 0;
	m_bLightDiffuse = true;
	m_bLightSpecular = true;

	//General lighting settings
	glEnable(GL_LIGHTING);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glShadeModel(GL_SMOOTH); //Gourad

	//Global ambient
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	//Set diffuse and specular light
	glLightfv(GL_LIGHT0, GL_AMBIENT, Color::Black);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Color::Black);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);	
	glLightfv(GL_LIGHT1, GL_AMBIENT, Color::Black);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Color::Black);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);	
}

void Scene::draw() {
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
	else {
		Camera::lookAt();
	}
	

	//Save the view matrix to be used later for eye position calculation
	m_dog->saveViewMatrix();

	//Light enabling and position
	if (m_bLightDiffuse) {
		glEnable(GL_LIGHT0);
		GLfloat lightPosition0[] = { 20, 40, 0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
	
		glEnable(GL_LIGHT1);
		GLfloat lightPosition1[] = { -20, 40, 0, 1.0 };
		glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	} else {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
	}
	m_lamp->setLighting(m_bLightSpecular);

	
	//Draw room
	glPushMatrix();
	glTranslatef(-Scene::ROOM_WIDTH / 2, 0, -Scene::ROOM_WIDTH / 2);
	m_room->draw();
	glPopMatrix();

	//Draw lamp
	m_lamp->draw(50, Scene::ROOM_HEIGHT, 20);
	
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
	
	//Debugging - Draw an item for position checking
	//glPushMatrix();
	//glTranslatef(40, 18, 11);
	//////Utils::drawSphere(1, 5, 5, FaceType::SOLID);
	//Utils::drawCube(1, 1, 1, FaceType::SOLID);
	//glPopMatrix();
	
	glutSwapBuffers();
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
	AppWindow::WORLD_FRONT_HEIGHT = 2 * (tan(Utils::radians(Camera::ANGLE / 2)))*(Camera::Z_NEAR);
	AppWindow::WORLD_FRONT_WIDTH = AppWindow::WORLD_FRONT_HEIGHT*AppWindow::ASPECT;
	AppWindow::WORLD_BACK_HEIGHT = 2 * (tan(Utils::radians(Camera::ANGLE / 2)))*(Camera::Z_FAR);
	AppWindow::WORLD_BACK_WIDTH = AppWindow::WORLD_BACK_HEIGHT*AppWindow::ASPECT;
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
	glutAddMenuEntry("Control lamp direction", KeysControl::LIGHT_DIRECTION);
	glutAddMenuEntry("Change light intensity", KeysControl::LIGHT_INTENSITY);

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
		case KeysControl::CAMERA_DOGVIEW:
		{
			if (m_bDogEyesView) {
				Utils::drawTextOnScreen("Camera is positioned at dog's eyes");
			}

			break;
		}
	}
}

void Scene::onKeyPress(unsigned char key, int x, int y) {
	switch (key) {
		case 'p':
		{
			m_curKeysControl = KeysControl::CAMERA_POSITION;
			break;
		}
		case 'e':
		{
			m_curKeysControl = KeysControl::CAMERA_LOOKAT;
			break;
		}
		case 'd':
		{
			m_bLightDiffuse = !m_bLightDiffuse;
			this->draw();
			break;
		}
		case 's':
		{
			m_bLightSpecular = !m_bLightSpecular;
			this->draw();
			break;
		}
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
		case KeysControl::LAMP_DIRECTION:
			this->handleLampDirection(key);
			break;
		case KeysControl::LIGHT_DIRECTION:
			this->handleLightPosition(key);
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
			Camera::rotateLookingPoint(1, 0, 0);
			Camera::lookAt();
			this->draw();

			break;
		}
		case GLUT_KEY_LEFT:
		{
			Camera::rotateLookingPoint(-1, 0, 0);
			Camera::lookAt();
			this->draw();

			break;
		}
		case GLUT_KEY_UP:
		{
			Camera::rotateLookingPoint(0, 1, 0);
			Camera::lookAt();
			this->draw();

			break;
		}
		case GLUT_KEY_DOWN:
		{
			Camera::rotateLookingPoint(0, -1, 0);
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

void Scene::handleLampDirection(unsigned char key)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
	{
		m_lamp->rotate(1, 0, 0);
		this->draw();
		break;
	}
	case GLUT_KEY_LEFT:
	{
		m_lamp->rotate(-1, 0, 0);
		this->draw();
		break;
	}
	case GLUT_KEY_UP:
	{
		m_lamp->rotate(0, 1, 0);
		this->draw();
		break;
	}
	case GLUT_KEY_DOWN:
	{
		m_lamp->rotate(0, -1, 0);
		this->draw();
		break;
	}
	case GLUT_KEY_PAGE_UP:
	{
		m_lamp->rotate(0, 0, -1);
		this->draw();
		break;
	}
	case GLUT_KEY_PAGE_DOWN:
	{
		m_lamp->rotate(0, 0, 1);
		this->draw();
		break;
	}
	}
}

void Scene::handleLightPosition(unsigned char key)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
	{
		lightRotatePosition(1, 0, 0);
		this->draw();

		break;
	}
	case GLUT_KEY_LEFT:
	{
		lightRotatePosition(-1, 0, 0);
		this->draw();

		break;
	}
	case GLUT_KEY_UP:
	{
		lightRotatePosition(0, 1, 0);
		this->draw();

		break;
	}
	case GLUT_KEY_DOWN:
	{
		lightRotatePosition(0, -1, 0);
		this->draw();

		break;
	}
	case GLUT_KEY_PAGE_UP:
	{
		lightRotatePosition(0, 0, -1);
		this->draw();

		break;
	}
	case GLUT_KEY_PAGE_DOWN:
	{
		lightRotatePosition(0, 0, 1);
		this->draw();

		break;
	}
	}
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
			m_dog->setTailAngle(0, 2);
			break;
		}
		case GLUT_KEY_DOWN:
		{
			m_dog->setTailAngle(0, -2);
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
		m_dog->setNeckAngle(4, 0);
		break;
	}
	case GLUT_KEY_LEFT:
	{
		m_dog->setNeckAngle(-4, 0);
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

void Scene::lightRotatePosition(int x, int y, int z) {
	m_LightPositionX += 2 * x;
	m_LightPositionY += 2 * y;
	m_LightPositionZ += 2 * z;
}