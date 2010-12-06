#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Bloc.h"
#include <vector>

class World
{

public:
	explicit World();

	void addHorizontal();
	void addVertical();

	void render(sf::RenderTarget *target);
	void step();
	
private:
//	QList<Bloc*> *blocs;
	std::vector<Bloc*> *blocs;
	b2Body *ground;
	b2World *world;
	sf::Shape groundShape;
	
	
//	QPolygonF poly;

	Bloc* createBloc();

};

#endif // WORLD_H
