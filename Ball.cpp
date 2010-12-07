#include "Ball.h"
#include <iostream>
#include "Const.h"

Ball::Ball(b2World *w) :
		world(w)
{
	drawable = sf::Shape::Circle(0,0, 5.f/SCALE, sf::Color(), -1.f/SCALE, sf::Color(200,0,0));
}

void Ball::impulse(int x, int y)
{
	b2Vec2 vect(x, y);
	body->ApplyLinearImpulse(vect, body->GetWorldCenter());
}

void Ball::adjust()
{
	b2Vec2 position = body->GetPosition();
	drawable.SetPosition(position.x, -position.y);
}

void Ball::setup()
{
	b2BodyDef bodyDef;
	b2CircleShape shape;
	shape.m_p.Set(0,0);
	shape.m_radius = 5.f/SCALE;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.5f;

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(drawable.GetPosition().x, -drawable.GetPosition().y);

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

}

sf::Shape* Ball::getDrawable()
{
	return &drawable;
}
