#include "Camera.h"

float Camera::EYE_X;
float Camera::EYE_Y;
float Camera::EYE_Z;
float Camera::LOOK_AT_X;
float Camera::LOOK_AT_Y;
float Camera::LOOK_AT_Z;
float Camera::VUP_X;
float Camera::VUP_Y;
float Camera::VUP_Z;
float Camera::ANGLE;
float Camera::Z_NEAR;
float Camera::Z_FAR;
float Camera::CAMERA_ANGLE;
float Camera::CAMERA_ANGLE_DEGREE;
float Camera::THETA;
float Camera::PHI;

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::init() {
	Camera::CAMERA_ANGLE = 0.0;
	Camera::CAMERA_ANGLE_DEGREE = 0.0;
	Camera::ANGLE = 90.0;
	Camera::Z_NEAR = 5.0;
	Camera::Z_FAR = 205.0;
	Camera::EYE_X = 50;
	Camera::EYE_Y = 20;
	Camera::EYE_Z = 40;
	Camera::LOOK_AT_X = 0;
	Camera::LOOK_AT_Y = 0;
	Camera::LOOK_AT_Z = 0;
	Camera::VUP_X = 0;
	Camera::VUP_Y = 1;
	Camera::VUP_Z = 0;
	Camera::THETA = 165.00f;
	Camera::PHI = 00.00f;
}

void Camera::rotatePosition(int x, int y, int z) {
	Camera::EYE_X += x;
	Camera::EYE_Y += y;
	Camera::EYE_Z += z;
}

void Camera::rotateLookingPoint(int x, int y, int z) {
	Camera::LOOK_AT_X += x;
	Camera::LOOK_AT_Y += y;
	Camera::LOOK_AT_Z += z;
}

void Camera::lookAt() {
	gluLookAt(
		Camera::EYE_X, Camera::EYE_Y, Camera::EYE_Z,
		Camera::LOOK_AT_X, Camera::LOOK_AT_Y, Camera::LOOK_AT_Z,
		Camera::VUP_X, Camera::VUP_Y, Camera::VUP_Z
	);
}

void Camera::lookAt(float eyeX, float eyeY, float eyeZ, float lookAtX, float lookAtY, float lookAtZ) {
	gluLookAt(
		eyeX, eyeY, eyeZ,
		lookAtX, lookAtY, lookAtZ,
		Camera::VUP_X, Camera::VUP_Y, Camera::VUP_Z
	);
}