#pragma once
#include "Mesh.h"

class Cone : public Mesh
{
public:
	void makeCone (float radius, int radialDivisions, int heightDivisions);

	Cone(void);
	~Cone(void);
};

