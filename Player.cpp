#include "Player.h"
#include "Const.h"
#include "Utils.h"
#include "Application.h"

Player::Player(b2World *w, sf::Color c) :
		Entity(w),
		color(c)
{
	fragility = 0.2f;
	canon = new Canon(color);

	player = new sf::Shape();
	redraw();
}

void Player::setCanonPos(float x, float y)
{
	canon->getDrawable()->SetPosition(x, y);
}

void Player::setPlayerPos(float x, float y)
{
	player->SetPosition(x, y);
}

void Player::redraw()
{
	if(pv > 0)
	{
		int green = (pv>80)? 200:80+pv;
		int red = (pv>95)? 100:250-pv;
		outlineColor = sf::Color(red,green,0);
	}
	else
		outlineColor = sf::Color(255,0,0);

	sf::Vector2f pos = player->GetPosition();
	float rot = player->GetRotation();
	shape = sf::Shape::Rectangle(-6.f/SCALE, -6.f/SCALE,
								 6.f/SCALE, 6.f/SCALE,
								 outlineColor, -2.f/SCALE, color);
	player = &shape;
	player->SetRotation(rot);
	player->SetPosition(pos);

}

void Player::render(sf::RenderTarget *t)
{
	t->Draw(*canon->getDrawable());
	t->Draw(*player);
}

void Player::setup()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(player->GetPosition().x, -player->GetPosition().y);
	bodyDef.angle = (Utils::deg2rad(player->GetRotation()));
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	shape.SetAsBox(6.f/SCALE, 6.f/SCALE);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.5f;
	fixtureDef.userData = this;

	body->CreateFixture(&fixtureDef);
}

void Player::deleteMe()
{
	Entity::deleteMe();
	redraw();
}

void Player::adjust()
{
	if(body)
	{
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		player->SetPosition(position.x, -position.y);
		player->SetRotation((Utils::rad2deg(angle)));
	}
}

void Player::onCollision(Entity *other)
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
