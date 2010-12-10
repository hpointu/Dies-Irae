#include "Entity.h"
#include <iostream>

Entity::Entity(b2World *w)
	: world(w),
	pv(100)
{
}


void Entity::onCollision(Entity *)
{
//	std::cout << "unhandled collision !" << std::endl;
}


b2Vec2 Entity::getVelocity()
{
	return body->GetLinearVelocity();
}


float Entity::getMass()
{
	return body->GetMass();
}

void Entity::deleteMe()
{
	world->DestroyBody(body);
	body = 0;
}
