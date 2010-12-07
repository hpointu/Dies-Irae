#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include "World.h"
#include "PausableClock.cpp"
#include "Utils.h"
#include "Singleton.h"

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;

public:
	void setup();
	void run();

	float getCurrentZoom();

private:
	Application();
	void eventManager();
	bool running;

	float currentZoom;

	Utils::MouseMode mouseMode;

	World *world;
	sf::RenderWindow window;
	sf::View *view;

	sf::Vector2f clickPos;
};

#endif // APPLICATION_H
