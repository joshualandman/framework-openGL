#include "Mesh.h"

void Mesh::initLocalUniforms()
{
}

void Mesh::addTriangle(float * data)
{
	for (int i = 0; i < 9; i++)
	{
		localVertexContainer.push_back(data[i]);
	}

	//Variables representing the {x,y,z} values of the three points, p1 p2 and p3:
	float p1[] = {data[0],data[1],data[2]};
	float p2[] = {data[3],data[4],data[5]};
	float p3[] = {data[6],data[7],data[8]};
	//Variables representing the {x,y,z} values of the ray from p1 to p2 and the ray from p1 to p3:
	float r12[] = {p2[0]-p1[0], p2[1]-p1[1], p2[2]-p1[2]};
	float r13[] = {p3[0]-p1[0], p3[1]-p1[1], p3[2]-p1[2]};
	//Variable representing the unit (magnitude 1) normal vector
	//Cross product r12 and r13 to get something perpendicular to them both
	float nx = r12[1]*r13[2] - r12[2]*r13[1];
	float ny = r12[2]*r13[0] - r12[0]*r13[2];
	float nz = r12[0]*r13[1] - r12[1]*r13[0];
	//Normalize the resulting cross product
	float normalMag = sqrt(nx*nx + ny*ny + nz*nz);
	nx = nx / normalMag;
	ny = ny / normalMag;
	nz = nz / normalMag;
	//Unit-Normal Vector
	float normal[] = {nx, ny, nz};
	//Push the normal vector onto the localNormalContainer once for each vertex
	/*Note: in the same way that our mesh actually duplicates vertices, so does it also duplicate
	normal vectors. However, for the purpose of this assignment, it is acceptable to do so. In
	industry or in your own projects, you may learn to load triangles as a strip, fan, or other more
	efficient structure, which would also allow the use of an equally efficient normal container.*/
	localNormalContainer.push_back(normal[0]);
	localNormalContainer.push_back(normal[1]);
	localNormalContainer.push_back(normal[2]);
	localNormalContainer.push_back(normal[0]);
	localNormalContainer.push_back(normal[1]);
	localNormalContainer.push_back(normal[2]);
	localNormalContainer.push_back(normal[0]);
	localNormalContainer.push_back(normal[1]);
	localNormalContainer.push_back(normal[2]);
}

//Initialize vertex data on the CPU
void Mesh::initTriangle1()
{
	float triangleData[9] = {   -.5,	-.5,	-.5,
									.5,	-.5,	-.5,
								-.5,	 .5,	-.5};

	addTriangle(triangleData);
}

//Initialize vertex data on the CPU
void Mesh::initTriangle2()
{
	float triangleData[9] = {    .5,	 .5,	 .5,
								-.5,	 .5,	-.5,
									.5,	-.5,	-.5};

	addTriangle(triangleData);
}

void Mesh::addSquare(float * square)
{
	float bottomLeft[] = {  square[0], square[1], square[2],
							square[3], square[4], square[5],
							square[6], square[7], square[8]};
	addTriangle(bottomLeft);

	float topRight[] = {square[9], square[10], square[11],
						square[6], square[7], square[8],
						square[3], square[4], square[5]};
	addTriangle(topRight);
}

Mesh::Mesh(void)
{
	initLocalUniforms();
}


Mesh::~Mesh(void)
{
}
