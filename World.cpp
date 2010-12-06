#include "World.h"
#include <iostream>
World::World()
{
//	blocs = new QList<Bloc*>();

	blocs = new std::vector<Bloc*>();
	
	world = new b2World(b2Vec2(0.0f, -9.81f), true);

	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	groundShape = sf::Shape::Rectangle(-100.f, -10.f, 100.f, 10.f, sf::Color(0,0,0,0), -1.f, sf::Color(255,255,255));

	groundShape.SetPosition(110.f, 100.f);
	
	bodyDef.position.Set(groundShape.GetPosition().x, -groundShape.GetPosition().y);

	shape.SetAsBox(100.f, 10.f);

	ground = world->CreateBody(&bodyDef);

	ground->CreateFixture(&fixtureDef);

	for(int i=0; i<10; i++)
	{
		Bloc *bloc = new Bloc(world);
		blocs->push_back(bloc);
//		bloc->getDrawable()->SetPosition(25.f+(i*25.f), 10.f);
		bloc->setup();
	}



}

void World::step()
{
	float32 tstep = 1.0f/20.0f;
	world->Step(tstep, 20, 20);
	for(int i=0; i<blocs->size(); i++)
		blocs->at(i)->adjust();
}

void World::addHorizontal()
{
/*	Bloc *bloc = createBloc();
	bloc->setup();
	this->addItem(bloc);*/
}

void World::addVertical()
{
	/*
	Bloc *bloc = createBloc();
	bloc->setRotation(90);
	bloc->setup();
	this->addItem(bloc);
	*/
}

Bloc* World::createBloc()
{
	
	Bloc *bloc = new Bloc(world);
/*
	blocs->append(bloc);
	bloc->setPos(-20 + qrand() % 40, -75 - qrand() % 150);
//	bloc->setPolygon(poly);
*/
	return bloc;
}

void World::render(sf::RenderTarget *target)
{
	for(int i=0; i<blocs->size(); i++)
		target->Draw(*blocs->at(i)->getDrawable());
	target->Draw(groundShape);
}
