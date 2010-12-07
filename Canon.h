#ifndef CANON_H
#define CANON_H

#include <SFML/Graphics.hpp>

class Canon
{
public:
    Canon();

	sf::Shape* getDrawable();

	void rotate(int offset = 5);
	void changePower(float offset);

	float getPower();

private:
	sf::Shape drawable;
	float power;

	void make();
};

#endif // CANON_H
