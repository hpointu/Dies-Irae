#include <SFML/Graphics.hpp>
#include <time.h>


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
	sf::RenderWindow window ;
	window.Create(sf::VideoMode(250, 170, 32), "Dies Irae", sf::Style::Close);

	while(window.IsOpened())
	{
		eventManager(window);
		window.Display();
	}

	return 0;
}
