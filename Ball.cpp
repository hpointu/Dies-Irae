#include "Ball.h"
#include <iostream>
#include "Const.h"

Ball::Ball(b2World *w)
	: Entity(w)
{
	drawable = sf::Shape::Circle(0,0, 5.f/SCALE, sf::Color(220,220,0), -1.f/SCALE, sf::Color(200,0,0));
	strength = 5.f;
}

void Ball::impulse(int x, int y)
{
	if(true)
	{
		b2Vec2 vect(x, y);
		body->ApplyLinearImpulse(vect, body->GetWorldCenter());
	}
}

void Ball::torque(float force)
{
	body->ApplyTorque(force);
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
	fixtureDef.restitution = 0.3f;
	fixtureDef.userData = this;

	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.position.Set(drawable.GetPosition().x, -drawable.GetPosition().y);

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	
	b2MassData data;
	body->GetMassData(&data);
	data.mass = data.mass*2;
	body->SetMassData(&data);
	
}

void Ball::render(sf::RenderTarget *t)
{
	t->Draw(drawable);
}

sf::Shape* Ball::getDrawable()
{
	return &drawable;
}
