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
#include "Player.h"

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

	inline Player* getCurrentPlayer(){return currentPlayer;}

	void nextPlayer();
	
private:
	std::vector<Bloc*> *blocs;
	std::vector<Ball*> *balls;
	std::vector<Player*> *players;

	Ball *perso;

	Ground *ground;

	b2World *world;
	Bloc *inactiveBloc;

	unsigned int currentPlayerId;
	Player *currentPlayer;





//	Canon *canon;
};

#endif // WORLD_H
