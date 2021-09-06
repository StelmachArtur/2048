#define _USE_MATH_DEFINES
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "Game.h"
#include<iostream>


using namespace sf;

int main()
{
	srand(time(NULL));
	unsigned int size = (VideoMode::getDesktopMode().height / 2) / 33 * 33; // since its integer calculation we make a size of window multiplicate of 33
	RenderWindow window(VideoMode(size, size), "2048", sf::Style::Titlebar | sf::Style::Close);
	Game game(&window, size/33,rand()%4,rand()%4);

	while (window.isOpen() and game.IsActive())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed) {
				game.KeyboardHandler(event);
			}
		}
		game.Update();
		game.Draw();
	}
	game.Update();
	game.Draw();

	system("pause");
	return 0;
}