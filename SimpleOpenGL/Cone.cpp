#include "Cone.h"

void Cone::makeCone (float radius, int radialDivisions, int heightDivisions)
{

	vector<float> x = subdivide(0,2*PI, radialDivisions);
	vector<float> y = subdivide(0,2*PI, radialDivisions);
	vector<float> z = subdivide(-.5, .5, heightDivisions);

	//draw ice cream cone
	for(int i = 0; i < x.size() - 1; i++)
	{
		for(int j = 0; j < z.size() - 1; j++)
		{
			u0 = i/((float) radialDivisions);
			u1 = (i+1)/((float) radialDivisions);
			v0 = j/((float) heightDivisions);
			v1 = (j+1)/((float) heightDivisions);

			float bob[9] = {radius * cos(x[i]) * (z[j]+0.5), radius * sin(y[i]) * (z[j]+0.5), z[j],
				radius * cos(x[i+1]) * (z[j]+0.5), radius *sin(y[i+1]) * (z[j]+0.5), z[j],
				radius * cos(x[i+1]) * (z[j+1]+0.5), radius * sin(y[i+1]) * (z[j+1]+0.5), z[j+1]
			};

			addTriangle(bob);
			addTexCoordTriangle(u0, u1, v0, v1);

			float bob2[9] = {radius * cos(x[i+1]) * (z[j+1]+0.5), radius * sin(y[i+1]) * (z[j+1]+0.5), z[j+1],
				radius * cos(x[i]) * (z[j+1]+0.5), radius *sin(y[i])* (z[j+1]+0.5), z[j+1],
				radius * cos(x[i]) * (z[j]+0.5), radius * sin(y[i]) * (z[j]+0.5), z[j]				
			};

			addTriangle(bob2);
			addTexCoordTriangle(u0, u1, v0, v1);
		}
	}

	for(int i = 0; i < y.size() - 1; i++)
	{
		v0 = i/((float) radialDivisions) +.5;
		u1 = (i+1)/((float) radialDivisions) + .5;

		//front face
		float bob[9] = {
			radius * cos(x[i]), radius * sin(y[i]), z[z.size()-1],			
			radius * cos(x[i+1]), radius * sin(y[i+1]), z[z.size()-1],
			0, 0, z[z.size()-1]
		};

		addTriangle(bob);
		addTexCoordTriangle(u0, u1, v0, v1);
	}
}


Cone::Cone(void) : Mesh()
{
	makeCone(1,20,20);
}


Cone::~Cone(void)
{
}
