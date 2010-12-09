#include "World.h"
#include "Const.h"
#include <iostream>
#include <math.h>
#include "Application.h"
#include "ContactListener.h"

World::World() :
		inactiveBloc(0)
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


	canon = new Canon();
	canon->getDrawable()->SetPosition(-350.f/SCALE, 235.f/SCALE);

//	perso = new Ball(world);
//	perso->getDrawable()->SetPosition(-300.f/SCALE, 130.f/SCALE);
//	perso->setup();
}

void World::accel(float force)
{
	perso->torque(force);
}


void World::rotateCanon(int offset)
{
	canon->rotate(offset);
}

void World::changeCanonPower(float offset)
{
	canon->changePower(offset);
}

void World::shoot()
{
	//perso->impulse(0.f, 30.f);
	Ball *ball = new Ball(world);
	ball->getDrawable()->SetPosition(canon->getDrawable()->GetPosition());
	balls->push_back(ball);
	ball->setup();

	float rot = canon->getDrawable()->GetRotation();
	rot = Utils::deg2rad(rot);
	float x = (10+(canon->getPower()*20))*cos(rot);
	float y = (10+(canon->getPower()*20))*sin(rot);

//	std::cout << "rot: " << rot << std::endl;
//	std::cout << x << "," << y << std::endl;

	ball->impulse(x, y);
}

void World::step()
{


	float32 tstep = 1.0f/20.0f;
	world->Step(tstep, 20, 20);
	for(int i=0; i<blocs->size(); i++)
		blocs->at(i)->adjust();
	for(int i=0; i<balls->size(); i++)
		balls->at(i)->adjust();
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
	for(int i=0; i<blocs->size(); i++)
		target->Draw(*blocs->at(i)->getDrawable());
	for(int i=0; i<balls->size(); i++)
		target->Draw(*balls->at(i)->getDrawable());
	target->Draw(ground->groundShape);
	target->Draw(*canon->getDrawable());
	if(inactiveBloc)
		target->Draw(*inactiveBloc->getDrawable());
	//target->Draw(*perso->getDrawable());
}
