#include "character.h"


Character::Character()
{
}


Character::~Character()
{
}


void Character::setPosition(float positionX, float positionY)
{
	this->positionX = positionX;
	this->positionY = positionY;
}


void Character::setParameters(float rotation, float speed, float dimension)
{
	this->rotation = rotation;
	this->speed = speed;
	this->dimension = dimension;
}


void Character::setScale(float scaleX, float scaleY)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}
