#pragma once

#include "utils/glm_utils.h"


class Projectile
{
public:
	float speed, distance, rotation;
	float positionX, positionY;

	Projectile(float positionX, float PositionY, float rotation, float speed, float distance);
	~Projectile();
};
