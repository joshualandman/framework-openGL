#pragma once
#include "Mesh.h"


class Cylinder : public Mesh
{
public:
	void makeCylinder (float radius, int radialDivisions, int heightDivisions);
	Cylinder(void);
	~Cylinder(void);
};

