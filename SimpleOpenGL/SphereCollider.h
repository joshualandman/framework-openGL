#pragma once
class SphereCollider
{
public:
	float radius;
	float position[3];
	bool collidesWith(SphereCollider other);
	SphereCollider(void);
	SphereCollider(float x, float y, float z, float r);
	~SphereCollider(void);
};

