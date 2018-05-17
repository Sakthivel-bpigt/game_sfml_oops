#include "game.h"


Game::Game(void)
	: bricks(gameWindow)
	, bullets(gameWindow, bricks)
{
	initialize();
	gameOver = false;
}


Game::~Game(void)
{
}

void Game::initialize()
{
	 gameWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Brick shooter");
	 windowSp.loadSprite("background.jpg");
	// bricks = 
	 //bricks.init(gameWindow);
}

bool Game::update()
{
	gameWindow.clear();
	gameWindow.draw(windowSp.get());

	return gameOver;
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
		gameOver = this->update();
		gameOver = bricks.update();
		gameOver = bullets.update();
		gameWindow.display();
	}
}