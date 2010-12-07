#include "Canon.h"
#include "Const.h"

Canon::Canon()
{
	drawable.AddPoint(0, -4.f/SCALE, sf::Color(), sf::Color(0,0,180));
	drawable.AddPoint(42.f/SCALE, -4.f/SCALE, sf::Color(), sf::Color(0,0,180));
	drawable.AddPoint(50.f/SCALE, 0/SCALE, sf::Color(), sf::Color(0,0,180));
	drawable.AddPoint(42.f/SCALE, 4.f/SCALE, sf::Color(), sf::Color(0,0,180));
	drawable.AddPoint(0, 4.f/SCALE, sf::Color(), sf::Color(0,0,180));

	drawable.EnableFill(false);
	drawable.SetOutlineWidth(-1.f/SCALE);
}

void Canon::rotate(int offset)
{
	drawable.SetRotation(drawable.GetRotation()+offset);
}

sf::Shape* Canon::getDrawable()
{
	return &drawable;
}
