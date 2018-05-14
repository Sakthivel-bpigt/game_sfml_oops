#include "game.h"


Game::Game(void)
{
	initialize();
}


Game::~Game(void)
{
}

void Game::initialize()
{
	 window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Brick shooter");
	 windowSp.loadSprite("background.jpg");
}

void Game::run()
{
	while (window.isOpen())
    {

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		window.clear();
		window.draw(windowSp.get());
		window.display();
	}
}