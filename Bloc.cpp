#include "Bloc.h"
#include <iostream>
Bloc::Bloc(b2World *w) :
	world(w),
	body(0),
	active(true)
{
	drawable = sf::Shape::Rectangle(-10.f, -2.f, 10.f, 2.f, sf::Color(255,255,0,0), -1.f, sf::Color(100,180,0));

	drawable.SetPosition(35+(rand()%80)*2, (rand()%10)*2);
	drawable.SetRotation(rand()%360);

}

sf::Shape* Bloc::getDrawable()
{
	return &drawable;
}

void Bloc::setup()
{


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(drawable.GetPosition().x, -drawable.GetPosition().y);
	bodyDef.angle = (Utils::deg2rad(drawable.GetRotation()));
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;	
	
	int n = drawable.GetNbPoints();
	
	b2Vec2 vertices[n];
//	std::cout << n << std::endl;
	
	for(int i=n-1; i>=0; i--)
	{
		sf::Vector2f p = drawable.GetPointPosition(i);
		vertices[i].Set(p.x, -(p.y));
//		std::cout << p.x << "," << -p.y << std::endl;
	}

	shape.SetAsBox(8.f, 2.f);

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
