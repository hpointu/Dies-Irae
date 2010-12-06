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

	sf::Shape sh = sf::Shape::Circle(0.f,0.f,100.f, sf::Color(0,0,0,0), 2.f, sf::Color(255,255,255));
	sh.SetPosition(100.f, 100.f);
	while(window.IsOpened())
	{
		window.Clear();
		eventManager(window);
		window.Draw(sh);
		window.Display();
	}

	return 0;
}
