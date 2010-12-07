#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include "World.h"
#include "PausableClock.cpp"
#include "Utils.h"

class Application
{
public:
    Application();

	void run();
private:
	void eventManager();

	bool running;

	Utils::MouseMode mouseMode;

	World world;
	sf::RenderWindow window;
};

#endif // APPLICATION_H
