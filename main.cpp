#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "PausableClock.cpp"
#include "World.h"
#include <iostream>
void eventManager(sf::RenderWindow &w)
{
	sf::Event Event;
	while(w.GetEvent(Event))
	{
		if(Event.Type == sf::Event::Closed)
		{
			w.Close();
		}
	}
}

int main(int argc, char *argv[])
{
	srand(time(0));
	
	sf::RenderWindow window ;
	sf::WindowSettings settings;
	settings.AntialiasingLevel = 2;
	window.Create(sf::VideoMode(250, 170, 32), "Dies Irae", sf::Style::Close, settings);

	PausableClock clock;
	clock.Play();

	World world;
	
	while(window.IsOpened())
	{
		window.Clear();
		eventManager(window);

		float speed = 0.01f;

		if(clock.GetElapsedTime() > speed)
		{
			world.step();
			clock.Reset();
		}

		
		world.render(&window);
		window.Display();
	}

	return 0;
}
