#include <stdlib.h>
#include <iostream>
#include "glew.h"
#include "glut.h"
#include <GL\GL.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
using namespace std;

#include "Window.h"
#include "Shader.h"
#include "VertexBufferObject.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Cube.h"
#include "Camera.h"
#include "Light.h"
#include "SOIL.h"
#include "GameObject.h"
#include "SphereCollider.h"
#include "Octree.h"

Window window1;
Shader shader1;
VertexBufferObject VBO;
Camera camera1;

//Declare more meshes here
//Sphere sphere1;
//Cylinder cylinder1;
//Cone cone1;
//Cube cube1;
VertexBufferObject sphereVBO;
VertexBufferObject cylinderVBO;
VertexBufferObject coneVBO;
VertexBufferObject cubeVBO;
VertexBufferObject modelVBO;
vector<GameObject> goVector;
GameObject cone;
GameObject cube;
GameObject cylinder;
GameObject sphere;
GameObject goModel;
Light light;
Light light2;
vector<SphereCollider> colliderVector;
Octree octree;

using namespace std;

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

void keyboard( unsigned char key, int x, int y )
{
    switch( key )
	{
		// Escape key
        case 033:	exit( 0 );
			        break;
		case 'w':	camera1.moveForward();
					break;
		case 'a':	camera1.moveLeft();
					break;
		case 's':	camera1.moveBackward();
					break;
		case 'd':	camera1.moveRight();
					break;
    } 
    
    glutPostRedisplay();
}

void mouseInit()
{
	//Hide the cursor for FPS-style mouselook
	glutSetCursor(GLUT_CURSOR_NONE);
}

void spawnSphere()
{
	SphereCollider* sphereCollision = new SphereCollider();
	Sphere* tempSphere = new Sphere();
	GameObject newTempSphere;
	tempSphere->makeSphere(1,1,1);
	newTempSphere.goMeshPointer = tempSphere;
	newTempSphere.goTextureID = int(shader1.groundTextureID);
	newTempSphere.transData[0] = camera1.lookat[0];
	newTempSphere.transData[1] = camera1.lookat[1];
	newTempSphere.transData[2] = camera1.lookat[2];
	sphereCollision->radius = 1;
	sphereCollision->position[0] = newTempSphere.transData[0];
	sphereCollision->position[1] = newTempSphere.transData[1];
	sphereCollision->position[2] = newTempSphere.transData[2];

	for(auto collid: octree.collection)
	{
		if(sphereCollision->collidesWith(collid))
		{
			delete tempSphere;
			delete sphereCollision;
			return;
		}
	}

	octree.add(*sphereCollision);
	newTempSphere.goVBO = &sphereVBO;
	goVector.push_back(newTempSphere);
	goVector.push_back(goModel);
	//colliderVector.push_back(*sphereCollision);
}

int loadObject(const char* fileName)
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

	//draw
	int num;
	num = glGenLists(1);
	
	glNewList(num, GL_COMPILE);

	for(int i = 0; i < faces.size(); i++)
	{
		if(faces[i]->quadOrTriangle)
		{
			glBegin(GL_QUADS);

				glNormal3f(normals[faces[i]->faceNumber-1]->x,normals[faces[i]->faceNumber-1]->y,normals[faces[i]->faceNumber-1]->z);
				glVertex3f(vertex[faces[i]->faces[0]-1]->x, vertex[faces[i]->faces[0]-1]->y, vertex[faces[i]->faces[0]-1]->z);
				glVertex3f(vertex[faces[i]->faces[1]-1]->x, vertex[faces[i]->faces[1]-1]->y, vertex[faces[i]->faces[1]-1]->z);
				glVertex3f(vertex[faces[i]->faces[2]-1]->x, vertex[faces[i]->faces[2]-1]->y, vertex[faces[i]->faces[2]-1]->z);
				glVertex3f(vertex[faces[i]->faces[3]-1]->x, vertex[faces[i]->faces[3]-1]->y, vertex[faces[i]->faces[3]-1]->z);
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);

				glNormal3f(normals[faces[i]->faceNumber-1]->x,normals[faces[i]->faceNumber-1]->y,normals[faces[i]->faceNumber-1]->z);
				glVertex3f(vertex[faces[i]->faces[0]-1]->x, vertex[faces[i]->faces[0]-1]->y, vertex[faces[i]->faces[0]-1]->z);
				glVertex3f(vertex[faces[i]->faces[1]-1]->x, vertex[faces[i]->faces[1]-1]->y, vertex[faces[i]->faces[1]-1]->z);
				glVertex3f(vertex[faces[i]->faces[2]-1]->x, vertex[faces[i]->faces[2]-1]->y, vertex[faces[i]->faces[2]-1]->z);

			glEnd();
		}
	}

	glEndList();

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

	return num;
}

void mouseclick(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch(button)
		{
			case GLUT_LEFT_BUTTON:	break;	// Left click functionality
			case GLUT_RIGHT_BUTTON:	break;	//Right click functionality
		}
	}

	spawnSphere();

	glutPostRedisplay();
}

void mouselook(int x, int y)
{
	float ms = .005; //mouse speed

	int dx = window1.width/2 - x;
	camera1.yaw += ms*float(dx)*camera1.proj[2];
		
	int dy = window1.height/2 - y;
	camera1.pitch += ms*float(dy)*camera1.proj[3];

	if (dx != 0 || dy != 0)
	{
		glutWarpPointer(window1.width/2,window1.height/2);
	}
	
	camera1.update();
	
	glutPostRedisplay();
}
int model;
void assetManagerInit()
{
	model = loadObject("test.obj");
	Mesh* modelMesh = new Mesh();
	modelVBO.gen();
	modelVBO.bind();
	modelVBO.loadBuffers(&(modelMesh->localVertexContainer),
						 &(modelMesh->localNormalContainer),
						 &(modelMesh->localTexCoordContainer));
	goModel.goMeshPointer = modelMesh;

	//Mesh* tempMesh = new Mesh();
	Cube* tempCube = new Cube();
	tempCube->makeCube(1);
	cubeVBO.gen();
	cubeVBO.bind();
	cubeVBO.loadBuffers( &(tempCube->localVertexContainer),
						 &(tempCube->localNormalContainer),
						 &(tempCube->localTexCoordContainer));
	cube.goMeshPointer = tempCube;

	//Mesh* tempConeMesh = new Mesh();
	Cone* tempCone = new Cone();
	tempCone->makeCone(1,1,1);
	coneVBO.gen();
	coneVBO.bind();
	coneVBO.loadBuffers(&(tempCone->localVertexContainer),
						 &(tempCone->localNormalContainer),
						 &(tempCone->localTexCoordContainer));
	cone.goMeshPointer = tempCone;

	//Mesh* tempCylinderMesh = new Mesh();
	Cylinder* tempCylinder = new Cylinder();
	tempCylinder->makeCylinder(1, 1, 1);
	cylinderVBO.gen();
	cylinderVBO.bind();
	cylinderVBO.loadBuffers(&(tempCylinder->localVertexContainer),
						 &(tempCylinder->localNormalContainer),
						 &(tempCylinder->localTexCoordContainer));
	cylinder.goMeshPointer = tempCylinder;

	//Mesh* tempSphereMesh = new Mesh();
	Sphere* tempSphere = new Sphere();
	tempSphere->makeSphere(1, 1, 1);
	sphereVBO.gen();
	sphereVBO.bind();
	sphereVBO.loadBuffers(&(tempSphere->localVertexContainer),
						 &(tempSphere->localNormalContainer),
						 &(tempSphere->localTexCoordContainer));
	sphere.goMeshPointer = tempSphere;	
}

void loadAndDrawGameObject(GameObject * goPtr)
{
	//Load this mesh's data into the shader program and the GPU vertex buffer
	//	Could be a waste of time reloading identical sets of vertices for subsequent objects with the same mesh data
	//	It may be necessary to load a different shader, too
	//VBO.loadBuffers( &(meshPtr->localVertexContainer), &(meshPtr->localNormalContainer), &(meshPtr->localTexCoordContainer));
	goPtr->goVBO->bind();
	int secondOffset = (goPtr->goMeshPointer->localVertexContainer).size() * sizeof(float);
	int thirdOffset = (goPtr->goMeshPointer->localNormalContainer).size() * sizeof(float) + secondOffset;
	//shader1.loadAttribute();			//Why does this have to go here?
	shader1.loadAttribs(secondOffset, thirdOffset);
	shader1.loadMeshUniforms(goPtr->thetaData, goPtr->scaleData, goPtr->transData);
	//shader1.loadTexture(meshPtr->textureFileName);
	//Draw what's on the GPU (Can we instead only draw a subset of the GPU data?)
	glBindTexture(GL_TEXTURE_2D, (goPtr->goTextureID));
	GLsizei count = goPtr->goMeshPointer->localVertexContainer.size() / 3;
	glDrawElements (GL_TRIANGLES, count,  GL_UNSIGNED_SHORT, (void *)0);
}

void draw( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	shader1.loadCameraUniforms(camera1.proj, camera1.eye, camera1.lookat, camera1.up);
	shader1.loadLightUniforms(light.lightPosition);
	shader1.loadLightUniforms(light2.lightPosition);

	glCallList(model);

	//load-and-draw more meshes here
	for (auto &go : goVector)
	{
		loadAndDrawGameObject(&go);
	}

	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit( &argc, argv );

	window1 = Window("New OpenGL Project", 800, 800);
	
	light2.lightPosition[2] = 6.;
	light2.lightPosition[1] = 1;

	glewInit();
		mouseInit();
	glutMouseFunc( mouseclick );
	glutPassiveMotionFunc( mouselook );
	glutKeyboardFunc( keyboard );
	glutDisplayFunc( draw );

	shader1 = Shader("vshader.glsl", "fshader.glsl");
	
	//VBO.init();
	assetManagerInit();

	shader1.loadTexture("SOIL.jpg", &(shader1.wallTextureID));
	shader1.loadTexture("wall.jpg", &(shader1.groundTextureID));
	shader1.loadTexture("SOIL.jpg", &(shader1.roofTextureID));
	
	sphere.goTextureID = int(shader1.groundTextureID);
	cylinder.goTextureID = int(shader1.roofTextureID);
	cone.goTextureID = int(shader1.roofTextureID);
	cube.goTextureID = int(shader1.wallTextureID);
	goModel.goTextureID = int(shader1.groundTextureID);

	sphere.transData[0] = 3.;
	//sphere.goMeshPointer->textureID = int(shader1.wallTextureID);
	sphere.goVBO = &sphereVBO;

	cylinder.transData[2] = 3.;
	cylinder.goVBO = &cylinderVBO;

	cone.transData[0] = -3.;
	cone.goVBO = &coneVBO;

	cube.transData[2] = -3.;
	cube.goVBO = &cubeVBO;

	goModel.transData[2] = 10.;
	goModel.goVBO = &modelVBO;

	goVector.push_back(cylinder);
	goVector.push_back(cone);
	goVector.push_back(cube);
	goVector.push_back(sphere);
	goVector.push_back(goModel);

    glutMainLoop();

	return 0;
}