#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>

class Entity
{
public:
	Entity(b2World *w);

	virtual void onCollision(Entity *other);

	virtual b2Vec2 getVelocity();
	virtual float getMass();

	virtual void deleteMe();

protected:
	b2World *world;
	b2Body *body;

	int pv;
};

#endif // ENTITY_H
