#pragma once

#include "Mesh.h"
#include "VertexBufferObject.h"

class GameObject
{
public:
	Mesh* goMeshPointer;
	VertexBufferObject* goVBO;
	char* goTextureFileName;
	int goTextureID;
	float thetaData[3];
	float transData[3];
	float scaleData[3];
	GameObject(void);
	~GameObject(void);
};

