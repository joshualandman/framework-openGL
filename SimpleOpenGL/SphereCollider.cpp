#include "SphereCollider.h"
#include <math.h>

SphereCollider::SphereCollider(void)
{
}

SphereCollider::SphereCollider(float x, float y, float z, float r)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	radius = r;
}

bool SphereCollider::collidesWith(SphereCollider col)
{
	float distX =pow((col.position[0] - this->position[0]),2);
	float distY =pow((col.position[1] - this->position[1]),2);
	float distZ =pow((col.position[2] - this->position[2]),2);

	float dist = (distX+distY+distZ);
	float sum = this->radius+col.radius;
	return(dist < pow(sum,2));
}

SphereCollider::~SphereCollider(void)
{
}
