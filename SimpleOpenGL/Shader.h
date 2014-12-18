#pragma once

#include <stdlib.h>
#include <iostream>
#include "glew.h"
#include "GL\x86\include\GL\glfw3.h"
//#include "glut.h"
#include <GL\GL.h>
#include "SOIL.h"
using namespace std;

#include "shaderProgram.h"
#include <vector>

class Shader
{
public:
	//Shader
	GLuint program;

	//Uniforms
	GLuint theta;
	GLuint trans;
	GLuint scale;

	GLuint proj;

	GLuint eye;
	GLuint lookat;
	GLuint up;

	GLuint vNormal;
	GLuint lightPosition;

	GLuint texture;
	GLuint vTexCoord;

	GLuint groundTextureID;
	GLuint wallTextureID;
	GLuint roofTextureID;

	void loadLightUniforms(float*);
	void loadAttribs(int secondOffset, int thirdOffset);

	//Varying (Attributes)
	GLuint vPosition;

	void loadMeshUniforms(float* , float* , float* );

	void loadCameraUniforms(float*, float*, float*, float*);

	void loadAttribute();

	void loadTexture(char* textureFileName, GLuint* textureIDPtr);

	Shader(char* , char* );

	Shader(void);
	~Shader(void);
};