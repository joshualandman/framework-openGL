#pragma once
#include "SphereCollider.h"
#include "AABBCollider.h"
#include <vector>
using namespace std;

class Node
{
public:
	int depth;
	bool hasChildren;
	vector<SphereCollider>* scvPtr;
	float center[3];
	int maxColliders;
	int maxDepth;
	float width;
	vector<Node> children;
	AABBCollider nodeCollider;
	vector<int> colliderIndices;

	void init()
	{
		hasChildren = false;
		maxColliders = 8;
		maxDepth = 4;
	}

	Node(float centerIn[], int depthIn, float widthIn, vector<SphereCollider>* ss)
	{
		init();

		center[0] = centerIn[0];
		center[1] = centerIn[1];
		center[2] = centerIn[2];

		scvPtr = ss;

		/*scvPtr->position[0] = center[0];
		scvPtr->position[1] = center[1];
		scvPtr->position[2] = center[2];
		scvPtr->radius = 1;*/
		//nodeCollider = AABBCollider(center[0], center[1], center[2], width);

		depth = depthIn;
		width = widthIn;
	}

	Node(void);
	~Node(void);

	void add(int sphereColliderIndex)
	{
		SphereCollider* sphereColliderPtr = &(*scvPtr)[sphereColliderIndex];

		if (hasChildren)
		{
			/*
			Use getIndex(position) to determine 
			which child this belongs to, then 
			call that child’s add method (colliderPtr).
			/**/
			//AABBCollider childAABB(sphereColliderPtr->position[0], sphereColliderPtr->position[1], sphereColliderPtr->position[2], sphereColliderPtr->radius);
			//AABBCollider(sphereColliderPtr->position[0], sphereColliderPtr->position[1], sphereColliderPtr->position[2], sphereColliderPtr->radius);
			for(auto &child : children)
			{
				if(child.detectCollision(sphereColliderPtr))
				{
					/*This method is why it's not working.
					The collider can overlap multiple nodes,
					But it's only being placed in the node
					that contains the collider's center/**/
					//int j = getIndex(sphereColliderPtr->position);
					child.add(sphereColliderIndex);
				}
			}
		}
		//if the node contains the maximum number of colliders and is not at the maximum depth, split the node
		else if ((colliderIndices.size() >= maxColliders) && (depth < maxDepth))
		{
			split();
			this->add(sphereColliderIndex);
		}
		//if none of the above, then add the collider to the node’s collection.
		else
		{
			colliderIndices.push_back(sphereColliderIndex);
		}
	}
	
	bool detectCollision(SphereCollider * sphereColliderPtr)
	{
		if (hasChildren)
		{
			/*returns someChild.detectCollision(colliderPtr). 
			It uses getKeyIndex to decide 
			which child should detect collisions./**/
			for(int i = 0; i < scvPtr->size(); i++)
			{
				if(sphereColliderPtr->collidesWith(scvPtr->at(i)))
				{
					//int i = getIndex(sphereColliderPtr->position);
					return true;
				}
			}
		}
		else
		{
			for (int i = 0; i < children.size(); i++)
			{
				//SphereCollider* newSphere = &(*scvPtr)[anotherInt];
				AABBCollider tempCollider = AABBCollider(center[0], center[1], center[2], width);
				if (tempCollider.collidesWith(sphereColliderPtr))
				{
					if(children[i].detectCollision(sphereColliderPtr))
					{
						return true;
					}
				}
			}
			return false;
		}
	}

	//getIndex and split... 
	//I wrote this equation to produce indices,
	//then wrote the split() function to agree with
	//these indices.
	/*int getIndex(float position[])
	{
		//I'll just leave this here.
		return int(position[0] > center[0])
			 + int(position[1] > center[1]) * 2
			 + int(position[2] > center[2]) * 4;
	}*/

	//split this node into 8 octants
	//and divide its colliders between the octants
	void split()
	{
		if (hasChildren) return;

		hasChildren = true;

		for (int k = -1; k <= 1; k+=2)//far, near
		{
			for (int j = -1; j <= 1; j+=2)//down, up
			{
				for (int i = -1; i <= 1; i+=2)//left, right
				{
					float newCenter[3];
					float halfWidth = width/2.;
					float qtrWidth = width/4.;

					newCenter[0] = center[0] + i * qtrWidth;
					newCenter[1] = center[1] + j * qtrWidth;
					newCenter[2] = center[2] + k * qtrWidth;
					//SphereCollider* sphere = new SphereCollider(newCenter[0], newCenter[1], newCenter[2], 1);
					//colliders.push_back(sphere);
					//nodeCollider = AABBCollider(newCenter[0], newCenter[1], newCenter[2], halfWidth);
					children.push_back(Node(newCenter, (int)depth+1, halfWidth,scvPtr));
				}
			}
		}
	
		while(colliderIndices.size() > 0)
		{
			add(colliderIndices[colliderIndices.size() - 1]);
			colliderIndices.pop_back();
		}
	}
};

class Octree
{
public:
	Node root;
	vector<SphereCollider> collection;

	Octree(void);
	~Octree(void);

	void add(SphereCollider sphereCollider)
	{
		collection.push_back(sphereCollider);
		root.add(collection.size()-1);

		/*if(!detectCollision(&sphereCollider))
		{
			collection.push_back(sphereCollider);
			SphereCollider * sphereColliderPtr = &collection[collection.size() - 1];
			/*AABBCollider aabbColliderPtr(sphereCollider.position[0],sphereCollider.position[1], sphereCollider.position[2],  );
			aabbColliderPtr->sphereCenter[0] = sphereColliderPtr->position[0];
			aabbColliderPtr->sphereCenter[1] = sphereColliderPtr->position[1];
			aabbColliderPtr->sphereCenter[2] = sphereColliderPtr->position[2];
			aabbColliderPtr->sphereRadius = 1;
			//root.nodeCollider = *aabbColliderPtr;
			root.add(sphereColliderPtr);
		}*/
	}

	bool detectCollision(SphereCollider * sphereColliderPtr)
	{
		return root.detectCollision(sphereColliderPtr);
	}

	bool detectCollision(SphereCollider sphereCollider)
	{
		return detectCollision(&sphereCollider);
	}
};