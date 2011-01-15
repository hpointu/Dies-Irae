#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

#include "Application.h"

// Test

int main(int argc, char *argv[])
{
	srand(time(0));

	Application *app = Application::getInstance();
	app->setup();
	app->run();

	return 0;
}
