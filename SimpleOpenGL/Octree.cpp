#include "Octree.h"

Node::Node(void)
{
	init();
}

Node::~Node(void)
{
}

Octree::Octree(void)
{
	float center[3] = {0.0,0.0,0.0};
	//SphereCollider* tempSphere = new SphereCollider(center[0], center[1], center[2], 1);
	root = Node(center,0,100,&collection);
}


Octree::~Octree(void)
{
}