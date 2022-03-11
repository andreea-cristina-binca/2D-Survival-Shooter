#pragma once

#include "utils/glm_utils.h"


class PickUp
{
public:
	float positionX, positionY;
	int type;

	PickUp(float positionX, float positionY, int type);
	~PickUp();

};
