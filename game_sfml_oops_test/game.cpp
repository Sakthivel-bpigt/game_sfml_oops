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
	 gameWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Brick shooter");
	 windowSp.loadSprite("background.jpg");
}

void Game::run()
{
	while (gameWindow.isOpen())
    {

		sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
        }

		gameWindow.clear();
		gameWindow.draw(windowSp.get());
		bricks.draw(gameWindow);
		gameWindow.display();
	}
}