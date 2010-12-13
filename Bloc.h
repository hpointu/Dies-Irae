#ifndef BLOC_H
#define BLOC_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Utils.h"

#include "Entity.h"

class Bloc : public Entity
{
public:
	explicit Bloc(b2World *w);

	virtual void setup();
	virtual void adjust();
	void actualizeBody();
	sf::Drawable* getDrawable();

	void stretch(float offset = 5);
	void enlarge(float offset = 5);

	virtual void redraw();

	virtual void onCollision(Entity *other);

	virtual void render(sf::RenderTarget *t);

protected:

	sf::Drawable *drawable;
	sf::Shape shape;

	bool active;

	float width;
	float height;

	sf::Color color;
};

#endif // BLOC_H
