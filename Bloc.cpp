#include "Bloc.h"
#include <iostream>
#include "Const.h"

Bloc::Bloc(b2World *w) :
		world(w),
		body(0),
		active(true),
		width(50.f/SCALE),
		height(8.f/SCALE)
{
	drawable = sf::Shape::Rectangle(-width/2, -height/2, width/2, height/2, sf::Color(255,255,0,0), -1.f/SCALE, sf::Color(100,180,0));

	drawable.SetPosition(35/SCALE+(rand()%80/SCALE)*2, (rand()%10/SCALE)*2);


}

sf::Shape* Bloc::getDrawable()
{
	return &drawable;
}

void Bloc::stretch(int offset)
{
	if(width+offset > 0)
	{
		width += offset;
		sf::Shape n = sf::Shape::Rectangle(-width/2, -height/2, width/2, height/2, sf::Color(255,255,0,0), -1.f/SCALE, sf::Color(100,180,0));;
		n.SetPosition(drawable.GetPosition());
		n.SetRotation(drawable.GetRotation());
		drawable = n;
	}
}

void Bloc::setup()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(drawable.GetPosition().x, -drawable.GetPosition().y);
	bodyDef.angle = (Utils::deg2rad(drawable.GetRotation()));
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	shape.SetAsBox(width/2, height/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.5f;

	body->CreateFixture(&fixtureDef);
}


void Bloc::actualizeBody()
{
	//	if(body)
	//		body->SetTransform(b2Vec2(x(), -y()), -(Utils::deg2rad(rotation())));

}

void Bloc::adjust()
{
	if(active)
	{
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		drawable.SetPosition(position.x, -position.y);
		drawable.SetRotation((Utils::rad2deg(angle)));
	}
}
