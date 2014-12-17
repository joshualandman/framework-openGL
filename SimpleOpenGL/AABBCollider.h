#pragma once
#include "SphereCollider.h"

class AABBCollider
{
public:
	//float sphereRadius;
	//float sphereCenter[3];
	float vertices[6];
	bool collidesWith(SphereCollider* sphereColliderPtr);
	AABBCollider(float centerX, float centerY, float centerZ, float width);
	float max(float x, float y);
	float min(float x, float y);
	AABBCollider(void);
	~AABBCollider(void);
};

