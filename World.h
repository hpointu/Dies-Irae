#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Bloc.h"
#include "Canon.h"
#include "Ball.h"
#include "Utils.h"
#include <vector>

class World
{

public:
	explicit World();

	Bloc* getInactiveBloc();

	void registerInactiveBloc();
	void clearInactiveBloc();

	void render(sf::RenderTarget *target);
	void step();

	void rotateCanon(int offset = 5);
	void changeCanonPower(float offset);

	void shoot();
	
private:
	std::vector<Bloc*> *blocs;
	std::vector<Ball*> *balls;

	b2Body *ground;

	b2World *world;

	sf::Shape groundShape;

	Bloc *inactiveBloc;

	Canon *canon;
};

#endif // WORLD_H
