#include "GameObject.h"


GameObject::GameObject(void)
{
	thetaData[0] = 0.0;
	thetaData[1] = 0.0;
	thetaData[2] = 0.0;

	scaleData[0] = 1.0;
	scaleData[1] = 1.0;
	scaleData[2] = 1.0;

	transData[0] = 0.0;
	transData[1] = 0.0;
	transData[2] = 0.0;
}


GameObject::~GameObject(void)
{
}
