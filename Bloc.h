#ifndef BLOC_H
#define BLOC_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Utils.h"

class Bloc
{
public:
	explicit Bloc(b2World *w, bool staticBloc = false);

	void setup();
	void adjust();
	void actualizeBody();
	sf::Shape* getDrawable();

	void stretch(float offset = 5);

private:
	b2World *world;
	b2Body *body;
	sf::Shape drawable;
	bool active;
	bool staticBloc;

	float width;
	float height;
};

#endif // BLOC_H
