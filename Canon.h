#ifndef CANON_H
#define CANON_H

#include <SFML/Graphics.hpp>

class Canon
{
public:
    Canon();

	sf::Shape* getDrawable();

	void rotate(int offset = 5);

private:
	sf::Shape drawable;
};

#endif // CANON_H
