#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Ball
{
public:
	Ball(b2World *w);

	void setup();
	void adjust();

	void impulse(int x, int y);

	sf::Shape* getDrawable();

private:
	b2World *world;
	b2Body *body;
	sf::Shape drawable;
};

#endif // BALL_H
