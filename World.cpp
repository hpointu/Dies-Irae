#include "World.h"
#include "Const.h"
#include <iostream>
#include <math.h>
#include "Application.h"

World::World() :
		inactiveBloc(0)
{
	blocs = new std::vector<Bloc*>();
	balls = new std::vector<Ball*>();
	
	world = new b2World(b2Vec2(0.0f, -9.81f), true);

	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	groundShape = sf::Shape::Rectangle(-350.f/SCALE, -10.f/SCALE, 350.f/SCALE, 10.f/SCALE,
									   sf::Color(0,0,0,0),
									   -1.f/SCALE,
									   sf::Color(255,255,255));

	groundShape.SetPosition(0, 150.f/SCALE);
	
	bodyDef.position.Set(groundShape.GetPosition().x, -groundShape.GetPosition().y);

	shape.SetAsBox(350.f/SCALE, 10.f/SCALE);

	ground = world->CreateBody(&bodyDef);

	ground->CreateFixture(&fixtureDef);

	for(int i=0; i<0; i++)
	{
		Bloc *bloc = new Bloc(world);
		blocs->push_back(bloc);
		bloc->getDrawable()->SetRotation(rand()%360);
		bloc->setup();
	}


	canon = new Canon();
	canon->getDrawable()->SetPosition(-350.f/SCALE, 135.f/SCALE);
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
}

Bloc* World::getInactiveBloc(bool staticBloc)
{
	if(!inactiveBloc)
	{
		inactiveBloc = new Bloc(world, staticBloc);
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
	target->Draw(groundShape);
	target->Draw(*canon->getDrawable());
	if(inactiveBloc)
		target->Draw(*inactiveBloc->getDrawable());
}
