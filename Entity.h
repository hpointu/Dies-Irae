#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(b2World *w);

	virtual void onCollision(Entity *other);

	virtual b2Vec2 getVelocity();
	virtual float getMass();

	virtual void deleteMe();

	virtual void render(sf::RenderTarget *t) = 0;

	inline float getStrength()
	{
		return strength;
	}

protected:
	b2World *world;
	b2Body *body;

	int pv;
	
	float fragility;
	float strength;
};

#endif // ENTITY_H
