#include "DBloc.h"
#include "Const.h"
#include <math.h>
#include <iostream>
#include "Application.h"
#include "ImgAnim.h"

DBloc::DBloc(b2World *w)
	: Bloc(w)
{
	fragility = 0.9f;
	redraw();
	explodeImg = new sf::Image();
	explodeImg->LoadFromFile("img/explode.png");
	
}


void DBloc::setup()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(drawable->GetPosition().x, -drawable->GetPosition().y);
	bodyDef.angle = (Utils::deg2rad(drawable->GetRotation()));
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	shape.SetAsBox(width/2, height/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.5f;
	fixtureDef.userData = this;
	fixtureDef.restitution = 0.1;

	body->CreateFixture(&fixtureDef);
}

void DBloc::redraw()
{
	if(pv > 0)
	{
		int green = (pv>80)? 200:80+pv;
		int red = (pv>95)? 100:250-pv;
		color = sf::Color(red,green,0);
	}
	else
		color = sf::Color(255,0,0);
	Bloc::redraw();
}

void DBloc::deleteMe()
{
	Bloc::deleteMe();
	color = sf::Color(100,100,100, 0);
/*
	sf::Vector2f npos = drawable->GetPosition();
	npos.y -= height/2/SCALE;
	npos.x -= width/2/SCALE;

	ImgAnim *img = new ImgAnim(*explodeImg, 2, 1,
										npos,
										sf::Vector2f(1.f/SCALE, 1.f/SCALE),
										drawable->GetRotation());
	img->setDelay(1.f);
	drawable = img;
*/	
	Bloc::redraw();
}

void DBloc::onCollision(Entity *other)
{
	if(pv > 0)
	{
		// other velocity is hurting me
		b2Vec2 velo = other->getVelocity();
		float val = ::sqrt((velo.x*velo.x) + (velo.y*velo.y));

		// other strength
		val *= other->getStrength();

		// ratio : other's mass VS mine. Who is the stronger ?
		val *= other->getMass()/getMass();

		// my own velocity is hurting me
		velo = getVelocity();
		val += ::sqrt((velo.x*velo.x) + (velo.y*velo.y))/2;

		// fragility factor
		val *= fragility;
		
		// I don't care about scratches
		if(val>=2 && pv > 0)
			pv -= val;

		if(pv <= 0)
			Application::getInstance()->enqueueToDelete(this);

		redraw();
	}
}
