#pragma once

#include "utils/glm_utils.h"


class Character
{
public:
	float positionX, positionY;
	float speed, rotation, dimension;
	float scaleX, scaleY;

	Character();
	~Character();

	void setPosition(float positionX, float positionY);
	void setParameters(float rotation, float speed, float dimension);
	void setScale(float scaleX, float scaleY);
};
