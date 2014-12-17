#include "Shader.h"

void Shader::loadMeshUniforms(float * thetaData, float * scaleData, float * transData)
{
	glUniform3fv (theta, 1, thetaData);
	glUniform3fv (scale, 1, scaleData);
	glUniform3fv (trans, 1, transData);
}

void Shader::loadCameraUniforms(float * projData, float * eyeData, float * lookatData, float * upData)
{
	glUniform4fv (proj, 1, projData);
	glUniform3fv (eye, 1, eyeData);
	glUniform3fv (lookat, 1, lookatData);
	glUniform3fv (up, 1, upData);
}

void Shader::loadLightUniforms(float* lightPositionData)
{
	glUniform3fv (lightPosition, 1, lightPositionData);
}

void Shader::loadAttribs(int secondOffset, int thirdOffset)
{
	glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, ((void*)0));
	glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, ((void*)secondOffset));
	glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, ((void*)thirdOffset));
}

void Shader::loadAttribute()
{
	glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, ((char *)NULL ));
}

Shader::Shader(char* vertexShaderFile, char* fragmentShaderFile)
{
	//Activating culling and drawing behavior
	glEnable( GL_DEPTH_TEST ); 
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	//Initialize Shader, its Uniforms, and its Attributes

	//Shader
	program = setUpAShader( vertexShaderFile, fragmentShaderFile );
	if (!program) {
		cerr << "Error setting up shaders" << endl;
		exit(1);
	}
	glUseProgram( program );

	//Uniforms
	theta	= glGetUniformLocation(program, "theta");
	trans	= glGetUniformLocation(program, "trans");
	scale	= glGetUniformLocation(program, "scale");

	proj	= glGetUniformLocation(program, "proj");

	eye		= glGetUniformLocation(program, "eye");
	lookat	= glGetUniformLocation(program, "lookat");
	up		= glGetUniformLocation(program, "up");

	lightPosition = glGetUniformLocation(program, "lightPosition");

	//Varying (Attributes)
	vPosition = glGetAttribLocation(program, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vNormal = glGetAttribLocation(program, "vNormal" );
	glEnableVertexAttribArray( vNormal );

	vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);

	//texture = glGetUniformLocation(program, "texture");
	//glBindTexture(GL_TEXTURE_2D, texture);
}
void Shader::loadTexture(char* textureFileName, GLuint* textureIDPtr)
{
	*textureIDPtr = SOIL_load_OGL_texture(
	textureFileName,
	SOIL_LOAD_AUTO,
	SOIL_CREATE_NEW_ID,
	SOIL_FLAG_INVERT_Y);
}

Shader::Shader(void)
{
}


Shader::~Shader(void)
{
}
