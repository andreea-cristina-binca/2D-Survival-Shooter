#include "obstacle.h"


Obstacle::Obstacle()
{
	this->positionX = 0;
	this->positionY = 0;
	this->scaleX = 1;
	this->scaleY = 1;
	this->dimension = 1;
}


Obstacle::~Obstacle()
{
}


void Obstacle::setPosition(float positionX, float positionY)
{
	this->positionX = positionX;
	this->positionY = positionY;
}


void Obstacle::setDimension(float dimesion)
{
	this->dimension = dimension;
}


void Obstacle::setScale(float scaleX, float scaleY)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}
