/*#include "ObjLoader.h"
using namespace std;

int ObjLoader::loadObject(const char* fileName)
{
	vector<string*> coord;
	vector<coordinate*> vertex;
	vector<face*> faces;
	vector<coordinate*> normals;

	ifstream readIn(fileName);
	if(!readIn.is_open())
	{
		cout << "Not Opened" << endl;
		return -1;
	}

	char buff[256];
	while(!readIn.eof())
	{
		readIn.getline(buff,256);
		coord.push_back(new string(buff));
	}

	for(int i = 0; i < coord.size(); i++)
	{
		if(((*coord[i])[0]) == '#')
		{
			continue;
		}
		else if(((*coord[i])[0]) == 'v' && (((*coord[i])[1]) == ' '))
		{
			float tempx, tempy, tempz;
			sscanf(coord[i]->c_str(),"v %f %f %f", &tempx, &tempy, &tempz);
			vertex.push_back(new coordinate(tempx, tempy, tempz));
		}
		else if(((*coord[i])[0]) == 'v' && (((*coord[i])[1]) == 'n'))
		{
			float tempx, tempy, tempz;
			sscanf(coord[i]->c_str(),"vn %f %f %f", &tempx, &tempy, &tempz);
			normals.push_back(new coordinate(tempx, tempy, tempz));
		}
		else if(((*coord[i])[0]) == 'f')
		{
			int a, b, c, d, e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==4)
			{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d%d//%d%d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
				faces.push_back(new face(b, a, c, d, e));
			}
			else
			{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d%d//%d%d//%d", &a, &b, &c, &b, &d, &b);
				faces.push_back(new face(b, a, c, d));
			}
		}
	}

	int num;
	glGenLists(


	for(int i = 0; i < coord.size(); i++)
	{
		delete coord[i];
	}
	for(int i =0; i <faces.size(); i++)
	{
		delete faces[i];
	}
	for(int i =0; i <normals.size(); i++)
	{
		delete normals[i];
	}
	for(int i =0; i <vertex.size(); i++)
	{
		delete vertex[i];
	}
}


ObjLoader::ObjLoader(void)
{
}


ObjLoader::~ObjLoader(void)
{
}
*/