#pragma once

#include "utils/glm_utils.h"


class Obstacle
{
public:
	float positionX, positionY;
	float dimension;
	float scaleX, scaleY;

	Obstacle();
	~Obstacle();

	void setPosition(float positionX, float positionY);
	void setDimension(float dimesion);
	void setScale(float scaleX, float scaleY);
};
