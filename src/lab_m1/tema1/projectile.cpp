#include "projectile.h"


Projectile::Projectile(float positionX, float PositionY, float rotation, float speed, float distance)
{
	this->positionX = positionX;
	this->positionY = PositionY;
	this->rotation = rotation;
	this->speed = speed;
	this->distance = distance;
}


Projectile::~Projectile()
{
}
