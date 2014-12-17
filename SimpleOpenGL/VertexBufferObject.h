#pragma once

#include <stdlib.h>
#include <iostream>
#include "glew.h"
#include "glut.h"
#include <GL\GL.h>
using namespace std;

#include <vector>

class VertexBufferObject
{
public:
	//Buffers
	GLuint buffer;
	GLuint ebuffer;
	int size;

	void loadBuffers(vector<float>*, vector<float>*, vector<float>* localTexCoordBufferPtr);

	void bind();
	void gen();

	VertexBufferObject(void);
	~VertexBufferObject(void);
};