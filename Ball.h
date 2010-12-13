#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(b2World *w);

	void setup();
	void adjust();

	void impulse(int x, int y);

	void torque(float force);

	sf::Shape* getDrawable();
	virtual void render(sf::RenderTarget *t);

private:
	sf::Shape drawable;
};

#endif // BALL_H
