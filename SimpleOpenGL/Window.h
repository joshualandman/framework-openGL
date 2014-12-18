#pragma once

#include <stdlib.h>
#include <iostream>
#include "glew.h"
#include "GL\x86\include\GL\glfw3.h"
//#include "glut.h"
#include <GL\GL.h>
using namespace std;

class Window
{
public:
	int height;
	int width;
	GLFWwindow* win;
	Window(char*, int, int );

	Window(void);
	~Window(void);
};

