#include "Sphere.h"

void Sphere::makeSphere (float radius, int slices, int stacks)
{
	vector<float> theta = subdivide(0,2*PI, slices);
	vector<float> phi = subdivide(-PI/2,PI/2, stacks);

	for(int i = 0; i < phi.size() -1; i++)
	{
		for(int j = 0; j < theta.size() - 1; j++)
		{
			u0 = i/((float) slices);
			u1 = (i+1)/((float) slices);
			v0 = j/((float) stacks);
			v1 = (j+1)/((float) stacks);

			float bob[9] = {radius * cos(theta[j+1]) * cos(phi[i+1]), radius * sin(theta[j+1]) * cos(phi[i+1]), radius *  sin(phi[i+1]),
				radius * cos(theta[j]) * cos(phi[i+1]), radius * sin(theta[j]) * cos(phi[i+1]), radius * sin(phi[i+1]),				
				radius * cos(theta[j]) * cos(phi[i]), radius * sin(theta[j]) * cos(phi[i]), radius * sin(phi[i])
			};

			addTriangle(bob);
			addTexCoordTriangle(u0, u1, v0, v1);

			float bob2[9] = {radius * cos(theta[j]) * cos(phi[i]), radius * sin(theta[j]) * cos(phi[i]), radius *  sin(phi[i]),
				radius * cos(theta[j+1]) * cos(phi[i]), radius * sin(theta[j+1]) * cos(phi[i]), radius * sin(phi[i]),
				radius * cos(theta[j+1]) * cos(phi[i+1]), radius * sin(theta[j+1]) * cos(phi[i+1]), radius * sin(phi[i+1])
			};

			addTriangle(bob2);
			addTexCoordTriangle(u0, u1, v0, v1);
		}
	}
}


Sphere::Sphere(void) : Mesh()
{
	makeSphere(1,20,20);
}


Sphere::~Sphere(void)
{
}
