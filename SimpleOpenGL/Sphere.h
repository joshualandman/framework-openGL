#pragma once
#include "Mesh.h"

class Sphere : public Mesh
{
public:
	void makeSphere (float radius, int slices, int stacks);

	Sphere(void);
	~Sphere(void);
};

