#pragma once

#include <stdlib.h>
#include <iostream>
#include "glew.h"
#include "glut.h"
#include <GL\GL.h>
using namespace std;

class Window
{
public:
	int height;
	int width;

	Window(char*, int, int );

	Window(void);
	~Window(void);
};

