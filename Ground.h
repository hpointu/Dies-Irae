#ifndef GROUND_H
#define GROUND_H

#include <Box2D/Box2D.h>

#include "Entity.h"
#include <SFML/Graphics.hpp>

class Ground : public Entity
{
public:
	Ground(b2World *w);

	void setup();
	sf::Shape groundShape;

};

#endif // GROUND_H
