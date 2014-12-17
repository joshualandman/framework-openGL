#pragma once

using namespace std;

#include <vector>
#include "Pi.h"
#include "Lerp.h"
#include "VertexBufferObject.h"

class Mesh
{
public:
	//Local vertex buffer
	vector<float> localVertexContainer;
	vector<float> localNormalContainer;
	vector<float> localTexCoordContainer;

	int textureID;
	float u0, u1, v0, v1;

	VertexBufferObject vboPtr;

	void addTexCoordTriangle(float u0, float u1, float v0, float v1)
	{
		localTexCoordContainer.push_back(u0);
		localTexCoordContainer.push_back(v0);

		localTexCoordContainer.push_back(u1);
		localTexCoordContainer.push_back(v0);

		localTexCoordContainer.push_back(u0);
		localTexCoordContainer.push_back(v1);

		//top right
		localTexCoordContainer.push_back(u1);
		localTexCoordContainer.push_back(v1);

		localTexCoordContainer.push_back(u0);
		localTexCoordContainer.push_back(v1);

		localTexCoordContainer.push_back(u1);
		localTexCoordContainer.push_back(v0);
	}

	vector<float> subdivide(float min, float max, int count)
	{
		vector<float> elements;

		float delta = (max - min) / float(count - 1);
		float value = min;

		for (int i = 0; i < count; i++)
		{		
			elements.push_back(value);
			value += delta;
		}

		return elements;
	}

	char* textureFileName;

	//Initialize local uniform data (model-world transformation data)
	void initLocalUniforms();

	void addTriangle(float * );

	//Initialize vertex data on the CPU
	void initTriangle1();

	//Initialize vertex data on the CPU
	void initTriangle2();

	void addSquare(float * );

	Mesh(void);
	~Mesh(void);
};