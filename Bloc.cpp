#include "Bloc.h"
#include <iostream>
#include "Const.h"

Bloc::Bloc(b2World *w) :
		Entity(w),
		active(true),
		width(8.f/SCALE),
		height(50.f/SCALE)
{
	color = sf::Color(255, 255, 255);
	drawable.SetPosition(35/SCALE+(rand()%80/SCALE)*2, (rand()%10/SCALE)*2);
	redraw();
}

void Bloc::redraw()
{
	sf::Vector2f pos = drawable.GetPosition();
	float rot = drawable.GetRotation();

	drawable = sf::Shape::Rectangle(-width/2, -height/2, width/2, height/2, sf::Color(100,255,0,0), -1.f/SCALE, color);

	drawable.SetRotation(rot);
	drawable.SetPosition(pos);
}

sf::Shape* Bloc::getDrawable()
{
	return &drawable;
}

void Bloc::stretch(float offset)
{
	offset /= SCALE;
	if(height+offset > 1.f/SCALE)
	{
		height += offset;
		redraw();
	}
}

void Bloc::enlarge(float offset)
{
	offset /= SCALE;
	if(width+offset > 1.f/SCALE)
	{
		width += offset;
		redraw();
	}
}

void Bloc::setup()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(drawable.GetPosition().x, -drawable.GetPosition().y);
	bodyDef.angle = (Utils::deg2rad(drawable.GetRotation()));
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	shape.SetAsBox(width/2, height/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.5f;
	fixtureDef.userData = this;

	body->CreateFixture(&fixtureDef);
}


void Bloc::onCollision(Entity *)
{

}

void Bloc::actualizeBody()
{
	//	if(body)
	//		body->SetTransform(b2Vec2(x(), -y()), -(Utils::deg2rad(rotation())));

}

void Bloc::adjust()
{
	if(active && body)
	{
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		drawable.SetPosition(position.x, -position.y);
		drawable.SetRotation((Utils::rad2deg(angle)));
	}
}
