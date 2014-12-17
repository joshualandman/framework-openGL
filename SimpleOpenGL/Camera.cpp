#include "Camera.h"

void Camera::update()
{
	if (pitch > PI/2.) pitch = PI/2.;	if (pitch < -PI/2.) pitch = -PI/2.;	

	lookat[0]= eye[0] - 1*cos(pitch)*sin(yaw);
	lookat[1]= eye[1] + 1*sin(pitch);
	lookat[2]= eye[2] + -1*cos(pitch)*cos(yaw);

	up[0]=-1*cos(pitch + PI/2.)*sin(yaw);
	up[1]= 1*sin(pitch + PI/2.);
	up[2]=-1*cos(pitch + PI/2.)*cos(yaw);
}

void Camera::moveForward()
{
	float moveSpeed = .1;
	eye[0] -= moveSpeed * sin(yaw);
	//eye[1] does not change
	eye[2] -= moveSpeed * cos(yaw);

	update();
}
		
void Camera::moveLeft()
{
	float moveSpeed = .1;
	eye[0] -= moveSpeed * cos(yaw);
	//eye[1] does not change
	eye[2] += moveSpeed * sin(yaw);

	update();
}
		
void Camera::moveBackward()
{
	float moveSpeed = .1;
	eye[0] += moveSpeed * sin(yaw);
	//eye[1] does not change
	eye[2] += moveSpeed * cos(yaw);

	update();
}
		
void Camera::moveRight()
{
	float moveSpeed = .1;
	eye[0] += moveSpeed * cos(yaw);
	//eye[1] does not change
	eye[2] -= moveSpeed * sin(yaw);

	update();
}

Camera::Camera(void)
{
	yaw = 0;
	pitch = 0;

	proj[0] = 1.;
	proj[1] = 100.;
	proj[2] = 1.;
	proj[3] = 1.;

	eye[0] = 0.;
	eye[1] = 0.;
	eye[2] = 0.;

	lookat[0] = 0.;
	lookat[1] = 0.;
	lookat[2] = -1.0;

	up[0] = 0.;
	up[1] = 1.;
	up[2] = 0.;
}

Camera::~Camera(void)
{
}
