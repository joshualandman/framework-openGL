#pragma once

#include <math.h>
#include "Pi.h"

class Camera
{
public:
	float yaw;
	float pitch;

	//projData = {nearPlane, farPlane, width, height}	
	float proj[4];

	float eye[3];
	float lookat[3];
	float up[3];
	
	void update();

	void moveForward();
		
	void moveLeft();
		
	void moveBackward();
		
	void moveRight();

	Camera(void);
	~Camera(void);
};

