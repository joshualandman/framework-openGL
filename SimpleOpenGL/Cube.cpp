#include "Cube.h"

void Cube::makeCube(int subdivisions)
{
	vector<float> x = subdivide(-.5, .5, subdivisions);
	vector<float> y = subdivide(-.5, .5, subdivisions);
	vector<float> z = subdivide(-.5, .5, subdivisions);


	//front
	for (int i = 0; i < x.size() - 1; i++)
	{
	 for (int j = 0; j < y.size() - 1; j++)
	 {

		u0 = i/((float) subdivisions);
		u1 = (i+1)/((float) subdivisions);
		v0 = j/((float) subdivisions);
		v1 = (j+1)/((float) subdivisions);

		 float bob[9] = { x[i+1], y[j+1], z[0],
		   x[i+1], y[j], z[0],
		   x[i], y[j], z[0]
		   };

		  addTriangle(bob);
		  addTexCoordTriangle(u0, u1, v0, v1);

		  float bob2[9] = { x[i], y[j], z[0],
		   x[i], y[j+1], z[0],
		   x[i+1], y[j+1], z[0]
		    };

		  addTriangle(bob2);
		  addTexCoordTriangle(u0, u1, v0, v1);
	 }
	}

	//back
	for (int i = 0; i < x.size() - 1; i++)
	{
	 for (int j = 0; j < y.size() - 1; j++)
	 {
		u0 = i/((float) subdivisions);
		u1 = (i+1)/((float) subdivisions);
		v0 = j/((float) subdivisions);
		v1 = (j+1)/((float) subdivisions);

		 float bob[9] = { x[i], y[j], z[z.size()-1],
		   x[i+1], y[j], z[z.size()-1],
		   x[i+1], y[j+1], z[z.size()-1]		   
		  };

		 addTriangle(bob);
		 addTexCoordTriangle(u0, u1, v0, v1);

		 float bob2[9] = {x[i+1], y[j+1], z[z.size()-1],
		   x[i], y[j+1], z[z.size()-1],
		   x[i], y[j], z[z.size()-1]
		 };

		 addTriangle(bob2);
		 addTexCoordTriangle(u0, u1, v0, v1);
	 }
	}

	//left
	for (int i = 0; i < x.size() - 1; i++)
	{
	 for (int j = 0; j < y.size() - 1; j++)
	 {

		u0 = i/((float) subdivisions);
		u1 = (i+1)/((float) subdivisions);
		v0 = j/((float) subdivisions);
		v1 = (j+1)/((float) subdivisions);

		 float bob[9] = {
			  x[i], y[0], z[j],
		   x[i+1], y[0], z[j],
		   x[i+1], y[0], z[j+1]		   
		 };

		 addTriangle(bob);
		 addTexCoordTriangle(u0, u1, v0, v1);

		  float bob2[9] = {x[i+1], y[0], z[j+1],
		   x[i], y[0], z[j+1],
		   x[i], y[0], z[j]		   
		  };

		  addTriangle(bob2);
		  addTexCoordTriangle(u0, u1, v0, v1);
	 }
	}

	//right
	for (int i = 0; i < x.size() - 1; i++)
	{
	 for (int j = 0; j < y.size() - 1; j++)
	 {
		u0 = i/((float) subdivisions);
		u1 = (i+1)/((float) subdivisions);
		v0 = j/((float) subdivisions);
		v1 = (j+1)/((float) subdivisions);

		  float bob[9] = {
			  x[i+1], y[y.size()-1], z[j+1],
		   x[i+1], y[y.size()-1], z[j],
		   x[i], y[y.size()-1], z[j]	   
		  };

		  addTriangle(bob);
		  addTexCoordTriangle(u0, u1, v0, v1);

		  float bob2[9] = {x[i], y[y.size()-1], z[j],
		   x[i], y[y.size()-1], z[j+1],
		   x[i+1], y[y.size()-1], z[j+1]
		  };

		  addTriangle(bob2);
		  addTexCoordTriangle(u0, u1, v0, v1);
	 }
	}

	//left on enter
	for (int i = 0; i < x.size() - 1; i++)
	{
	 for (int j = 0; j < y.size() - 1; j++)
	 {
		u0 = i/((float) subdivisions);
		u1 = (i+1)/((float) subdivisions);
		v0 = j/((float) subdivisions);
		v1 = (j+1)/((float) subdivisions);

		  float bob[9] = {
			x[0], y[j], z[i],
		   x[0], y[j], z[i+1],
		    x[0], y[j+1], z[i+1]		   
		  };

		  addTriangle(bob);
		  addTexCoordTriangle(u0, u1, v0, v1);

		  float bob2[9] = {
			  x[0], y[j+1], z[i+1],
		   x[0], y[j+1], z[i],
		   x[0], y[j], z[i]		   
		  };

		  addTriangle(bob2);
		  addTexCoordTriangle(u0, u1, v0, v1);
	 }
	}

	//right on enter
	for (int i = 0; i < x.size() - 1; i++)
	{
	 for (int j = 0; j < y.size() - 1; j++)
	 {

		u0 = i/((float) subdivisions);
		u1 = (i+1)/((float) subdivisions);
		v0 = j/((float) subdivisions);
		v1 = (j+1)/((float) subdivisions);

		  float bob[9] = {
			x[x.size()-1], y[j+1], z[i+1],
		   x[x.size()-1], y[j], z[i+1],
		    x[x.size()-1], y[j], z[i]		   
		  };

		  addTriangle(bob);
		  addTexCoordTriangle(u0, u1, v0, v1);

		  float bob2[9] = {
			x[x.size()-1], y[j], z[i],
		   x[x.size()-1], y[j+1], z[i],
		   x[x.size()-1], y[j+1], z[i+1]		  
		  };
		  
		  addTriangle(bob2);
		  addTexCoordTriangle(u0, u1, v0, v1);
	 }
	}
}

Cube::Cube(void) : Mesh()
{
	makeCube(10);
}


Cube::~Cube(void)
{
}
