#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

#include "Application.h"

/* Modification dans la branche master */
int main(int argc, char *argv[])
{
	// graine
	srand(time(0));

	Application *app = Application::getInstance();
	app->setup();
	app->run();

	return 0;
}
