#include "ContactListener.h"
#include <iostream>

ContactListener::ContactListener()
{

}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{

}

void ContactListener::BeginContact(b2Contact *contact)
{
	Entity *e1 = (Entity*) contact->GetFixtureA()->GetUserData();
	Entity *e2 = (Entity*) contact->GetFixtureB()->GetUserData();

	e1->onCollision(e2);
	e2->onCollision(e1);

//	std::cout << "e1: " << e1->getVelocity().x << "," << e1->getVelocity().y << std::endl;
//	std::cout << "e2: " << e2->getVelocity().x << "," << e2->getVelocity().y << std::endl;
}
