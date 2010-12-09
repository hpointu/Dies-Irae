#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Bloc.h"
#include "DBloc.h"
#include "Canon.h"
#include "Ball.h"
#include "Utils.h"
#include "Ground.h"

#include <vector>

class World
{

public:
	explicit World();

	Bloc* getInactiveBloc(bool staticBloc = false);

	void registerInactiveBloc();
	void clearInactiveBloc();

	void render(sf::RenderTarget *target);
	void step();

	void rotateCanon(int offset = 5);
	void changeCanonPower(float offset);

	void accel(float force);

	void shoot();
	
private:
	std::vector<Bloc*> *blocs;
	std::vector<Ball*> *balls;

	Ball *perso;

	Ground *ground;

	b2World *world;



	Bloc *inactiveBloc;

	Canon *canon;
};

#endif // WORLD_H
