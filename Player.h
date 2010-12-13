#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Canon.h"

class Player : public Entity
{
public:
	Player(b2World *w, sf::Color c);

	void setCanonPos(float x, float y);
	void setPlayerPos(float x, float y);

	inline Canon* getCanon(){return canon;}

	virtual void render(sf::RenderTarget *t);

	virtual void setup();
	virtual void adjust();

	virtual void redraw();

	virtual void onCollision(Entity *other);

	void deleteMe();
private:
	Canon *canon;
	sf::Color color;
	sf::Color outlineColor;
	sf::Drawable *player;
	sf::Shape shape;
};

#endif // PLAYER_H
