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
}

void Game::run()
{
	while (window.isOpen())
    {
		 window.display();
	}
}