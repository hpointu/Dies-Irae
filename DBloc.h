#ifndef DBLOC_H
#define DBLOC_H

#include <Box2D/Box2D.h>

#include "Bloc.h"
#include <SFML/Graphics.hpp>

class DBloc : public Bloc
{
public:
	DBloc(b2World *w);
	void setup();

	virtual void onCollision(Entity *other);

	virtual void redraw();

	virtual void deleteMe();
	
private:
	sf::Image *explodeImg;
	
};

#endif // DBLOC_H
