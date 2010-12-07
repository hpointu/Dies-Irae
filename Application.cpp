#include "Application.h"
#include "Const.h"
#include <iostream>
Application::Application() :
		running(false)
{
	sf::WindowSettings settings;
	settings.AntialiasingLevel = 2;
	window.Create(sf::VideoMode(750, 370, 32), "Dies Irae", sf::Style::Close, settings);

	sf::View *view = new sf::View(sf::Vector2f(0, 0), sf::Vector2f(375,185));
	view->Zoom(SCALE);
	window.SetView(*view);

	mouseMode = Utils::Normal;
}

void Application::run()
{
	if(!running)
	{
		PausableClock clock;
		clock.Play();

		running = true;
		while(window.IsOpened())
		{
			window.Clear();
			eventManager();

			float speed = 0.01f;

			if(clock.GetElapsedTime() > speed)
			{
				world.step();
				clock.Reset();
			}

			world.render(&window);
			window.Display();
		}
	}
}

void Application::eventManager()
{
	sf::Event e;

	while(window.GetEvent(e))
	{
		if(e.Type == sf::Event::Closed)
		{
			window.Close();
		}
		if(e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::A))
		{
			mouseMode = Utils::Add;
			int x = window.GetInput().GetMouseX();
			int y = window.GetInput().GetMouseY();
			Bloc *b = world.getInactiveBloc();
			b->getDrawable()->SetPosition(x,y);
		}
		if(e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::R))
		{
			if(mouseMode == Utils::Add)
			{
				Bloc *b = world.getInactiveBloc();
				b->getDrawable()->SetRotation(b->getDrawable()->GetRotation()-30);
			}
		}
		if(e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::S))
		{
			if(mouseMode == Utils::Add)
			{
				Bloc *b = world.getInactiveBloc();
				b->stretch();
			}
		}
		if(e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::Q))
		{
			if(mouseMode == Utils::Add)
			{
				Bloc *b = world.getInactiveBloc();
				b->stretch(-5);
			}
		}
		if(e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::Escape))
		{
			mouseMode = Utils::Normal;
			world.clearInactiveBloc();
		}
		if(e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::Left))
		{
			if(mouseMode == Utils::Normal)
			{
				world.rotateCanon(2);
			}
		}
		if(e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::Right))
		{
			if(mouseMode == Utils::Normal)
			{
				world.rotateCanon(-2);
			}
		}
		if((e.Type == sf::Event::MouseButtonPressed))
		{
			if(e.MouseButton.Button == sf::Mouse::Left && mouseMode == Utils::Add)
			{
				mouseMode = Utils::Normal;
				Bloc *b = world.getInactiveBloc();
				b->setup();
				world.registerInactiveBloc();
			}
		}
		if(e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::Space))
		{
			if(mouseMode == Utils::Normal)
			{
				world.shoot();
			}
		}
	}
	if(mouseMode == Utils::Add)
	{
		sf::Vector2f mousePos = window.ConvertCoords(window.GetInput().GetMouseX(), window.GetInput().GetMouseY());
		//sf::Vector2f mousePos(window.GetInput().GetMouseX(), window.GetInput().GetMouseY());
		float x = mousePos.x;
		float y = mousePos.y;
		std::cout << x << "," << y << std::endl;
		Bloc *b = world.getInactiveBloc();
		b->getDrawable()->SetPosition(x,y);
	}
}