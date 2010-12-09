#include "Ground.h"
#include "Const.h"

Ground::Ground(b2World *w)
	: Entity(w)
{

}

void Ground::setup()
{
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.userData = this;

	groundShape = sf::Shape::Rectangle(-350.f/SCALE, -10.f/SCALE, 350.f/SCALE, 10.f/SCALE,
									   sf::Color(0,0,0,0),
									   -1.f/SCALE,
									   sf::Color(255,255,255));

	groundShape.SetPosition(0, 250.f/SCALE);

	bodyDef.position.Set(groundShape.GetPosition().x, -groundShape.GetPosition().y);

	shape.SetAsBox(350.f/SCALE, 10.f/SCALE);

	body = world->CreateBody(&bodyDef);

	body->CreateFixture(&fixtureDef);
}
