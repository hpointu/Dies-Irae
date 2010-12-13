#include "World.h"
#include "Const.h"
#include <iostream>
#include <math.h>
#include "Application.h"
#include "ContactListener.h"

World::World() :
		inactiveBloc(0),
		currentPlayerId(0)
{
	blocs = new std::vector<Bloc*>();
	balls = new std::vector<Ball*>();
	
	world = new b2World(b2Vec2(0.0f, -9.81f), true);
	world->SetContactListener(new ContactListener());


	ground = new Ground(world);
	ground->setup();

	for(int i=0; i<0; i++)
	{
		Bloc *bloc = new Bloc(world);
		blocs->push_back(bloc);
		bloc->getDrawable()->SetRotation(rand()%360);
		bloc->setup();
	}


	Player *p1 = new Player(world, sf::Color(0,0,255));
	Player *p2 = new Player(world, sf::Color(255,255,0));

	players = new std::vector<Player*>();
	players->push_back(p1);
	players->push_back(p2);

	p1->setCanonPos(-350.f/SCALE, 205.f/SCALE);
	p2->setCanonPos(350.f/SCALE, 205.f/SCALE);

	p1->setPlayerPos(-400.f/SCALE, 230.f/SCALE);
	p2->setPlayerPos(400.f/SCALE, 235.f/SCALE);

	p1->setup();
	p2->setup();

	p1->getCanon()->rotate(60);
	p2->getCanon()->rotate(120);

	currentPlayer = players->at(currentPlayerId);

}

void World::nextPlayer()
{
	if(++currentPlayerId >= players->size())
		currentPlayerId = 0;

	currentPlayer = players->at(currentPlayerId);
}

void World::accel(float force)
{
	perso->torque(force);
}


void World::rotateCanon(int offset)
{
	currentPlayer->getCanon()->rotate(offset);
}

void World::changeCanonPower(float offset)
{
	currentPlayer->getCanon()->changePower(offset);
}

void World::shoot()
{
	Canon *canon = currentPlayer->getCanon();

	Ball *ball = new Ball(world);
	ball->getDrawable()->SetPosition(canon->getDrawable()->GetPosition());
	balls->push_back(ball);
	ball->setup();

	float rot = canon->getDrawable()->GetRotation();
	rot = Utils::deg2rad(rot);
	float x = (10+(canon->getPower()*20))*cos(rot);
	float y = (10+(canon->getPower()*20))*sin(rot);

	ball->impulse(x, y);

	nextPlayer();
}

void World::step()
{
	float32 tstep = 1.0f/20.0f;
	world->Step(tstep, 20, 20);
	for(unsigned int i=0; i<blocs->size(); i++)
		blocs->at(i)->adjust();
	for(unsigned int i=0; i<balls->size(); i++)
		balls->at(i)->adjust();
	for(unsigned int i=0; i<players->size(); i++)
		players->at(i)->adjust();
	world->ClearForces();

	Application::getInstance()->deleteEntities();
}

Bloc* World::getInactiveBloc(bool staticBloc)
{
	if(!inactiveBloc)
	{
		inactiveBloc = staticBloc ? new Bloc(world) : new DBloc(world);
	}
	return inactiveBloc;
}

void World::registerInactiveBloc()
{
	blocs->push_back(inactiveBloc);
	inactiveBloc = 0;
}

void World::clearInactiveBloc()
{
	delete inactiveBloc;
	inactiveBloc = 0;
}

void World::render(sf::RenderTarget *target)
{
	for(unsigned int i=0; i<blocs->size(); i++)
		blocs->at(i)->render(target);
	for(unsigned int i=0; i<balls->size(); i++)
		balls->at(i)->render(target);
	for(unsigned int i=0; i<players->size(); i++)
		players->at(i)->render(target);
	ground->render(target);

	if(inactiveBloc)
		target->Draw(*inactiveBloc->getDrawable());

}
