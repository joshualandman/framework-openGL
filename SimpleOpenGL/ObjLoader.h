#pragma once
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>

struct coordinate
{
	float x, y, z;
	coordinate(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}
};

struct face
{
	int faceNumber;
	bool quadOrTriangle;
	int faces[4];
	face(int faceN, int f1, int f2, int f3) : faceNumber(faceN)
	{
		faces[0] = f1;
		faces[1] = f2;
		faces[2] = f3;
		quadOrTriangle = false;
	}
	face(int faceN, int f1, int f2, int f3, int f4) : faceNumber(faceN)
	{
		faces[0] = f1;
		faces[1] = f2;
		faces[2] = f3;
		faces[3] = f4;
		quadOrTriangle = true;
	}
};

class ObjLoader
{
public:
	float angle;
	int loadObject(const char* fileName);
	ObjLoader(void);
	~ObjLoader(void);
};

