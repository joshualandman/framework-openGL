#include "VertexBufferObject.h"

void VertexBufferObject::loadBuffers(vector<float> * localVertexBufferPtr, vector<float>* localNormalBufferPtr, vector<float>* localTexCoordBufferPtr)
{
	size = localVertexBufferPtr->size();

	float* vertexArray = new float[size];
	float* normalArray = new float[size];
	float * texCoArray = new float[size*2/3];
	for (int i=0; i < size*2/3; i++)
	{
		texCoArray[i] = (*localTexCoordBufferPtr)[i];
	}

	for (int i=0; i < size; i++)
	{
		vertexArray[i] = (*localVertexBufferPtr)[i];
		normalArray[i] = (*localNormalBufferPtr)[i];
	}
	int dataSize = size * sizeof(float);
	int normSize = size * sizeof(float);
	int texCoSize = size*2/3 * sizeof(float);
	glBufferData( GL_ARRAY_BUFFER, dataSize + normSize + texCoSize, NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, dataSize + normSize, texCoSize, texCoArray);
	glBufferSubData( GL_ARRAY_BUFFER, 0, dataSize, vertexArray);
	glBufferSubData( GL_ARRAY_BUFFER, dataSize, normSize, normalArray);
	delete [] vertexArray;
	delete [] normalArray;

	/*float * vertexArray = new float[size];
	for (int i=0; i < size; i++)
	{
		vertexArray[i] = (*localVertexBufferPtr)[i];
	}
	int dataSize = size * sizeof (float);
	glBufferData( GL_ARRAY_BUFFER, dataSize, vertexArray, GL_STATIC_DRAW );
	delete [] vertexArray;
	*/
	//Element buffer
	GLushort * elementArray = new GLushort[size];
	for (int i=0; i < size; i++)
	{
		elementArray[i] = i;
	}
	int edataSize = size / 3 * sizeof (GLushort);
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, edataSize, elementArray, GL_STATIC_DRAW );
	delete [] elementArray;
}

void VertexBufferObject::bind()
{
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );
}

void VertexBufferObject::gen()
{
	glGenBuffers( 1, &buffer );
	glGenBuffers( 1, &ebuffer );	
}

VertexBufferObject::VertexBufferObject(void)
{
}

VertexBufferObject::~VertexBufferObject(void)
{
}
