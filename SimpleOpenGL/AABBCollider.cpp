#include "AABBCollider.h"

 AABBCollider::AABBCollider(float centerX, float centerY, float centerZ, float width)
{
	//sphereRadius = width;
	//sphereCenter[0] = centerX;
	//sphereCenter[1] = centerY;
	//sphereCenter[2] = centerZ;
	vertices[0] = centerX -width/2.;
	vertices[1] = centerY -width/2.;
	vertices[2] = centerZ -width/2.;
	vertices[3] = centerX +width/2.;
	vertices[4] = centerY +width/2.;
	vertices[5] = centerZ +width/2.;
}

 bool AABBCollider::collidesWith(SphereCollider* sphereColliderPtr)
 {
	float sphereRadius = sphereColliderPtr->radius;
	float* sphereCenter = sphereColliderPtr->position;

	float distSqrd=0;
	for(int i = 0; i <3; i++)
	{
		//coordinate value of the upper near right plane along this axis
		float vMax = max(vertices[i], vertices[3+i]);
		float vMin = min(vertices[i], vertices[3+i]);

		//distance(dosplacement) from sphere to planes along this axis
		float dMin = sphereCenter[i] - vMin;
		float dMax = sphereCenter[i] - vMax;

		//case 1: Sphere is below/beyond/left of the planes
		//case 2: Sphere is  above/before/right of the planes
		//case 3: Sphere is between the planes
		if (dMin < 0) distSqrd += dMin * dMin;
		else if (dMax > 0) distSqrd += dMax * dMax;
		//else       distSqrd += 0;
	}
	//compare distance squared to radius squared
	return (distSqrd <= sphereRadius * sphereRadius);
}

float AABBCollider::max(float x, float y)
{
	 if(x > y)
	 {
		 return x;
	 }
	 else
	 {
		 return y;
	 }
}

float AABBCollider::min(float x, float y)
{
	 if( x < y)
	 {
		 return x;
	 }
	 else
	 {
		 return y;
	 }
}

AABBCollider::AABBCollider(void)
{

}


AABBCollider::~AABBCollider(void)
{
}
