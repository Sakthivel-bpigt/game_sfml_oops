#include "game.h"


Game::Game(void)
	: bricks(gameWindow)
	, bullets(gameWindow, bricks)
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
	gameOver = true;
	gameStart = false;
	 setupPlayButton();
	 setupGameOverButton();
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

		if(gameOver)
		{
			if(!gameStart)
			{
				gameWindow.draw(playSp.get());
			}else
			{
				gameWindow.draw(gameOverSp.get());
			}
			if (gameTime.getElapsedTime().asSeconds() > START_GAP_TIME &&
				sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//while(gameTime.getElapsedTime().asSeconds() < START_GAP_TIME) {}
				gameTime.restart();
				gameStart = true;
				gameOver = false;
				gameRestart();
			}
		}else if(!gameOver)
		{
			if (gameTime.getElapsedTime().asSeconds() > START_GAP_TIME)
			{
				gameOver = bullets.update();
			}
			gameOver = bricks.update();
			//cout<<gameOver<<endl;
			if (gameOver)
			{
				gameTime.restart();
			}
		}

		gameWindow.display();
	}
}

void Game::setupPlayButton()
{
	//633 X 200
	 playSp.loadSprite("png/playgame.png");
	playSp.setOrigin(sf::Vector2f(316, 100));
	playSp.setPosition(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT /2));
}

void Game::setupGameOverButton()
{
	//480 X 360
	gameOverSp.loadSprite("png/game-over.png");
	gameOverSp.setOrigin(sf::Vector2f(240, 180));
	gameOverSp.setPosition(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT /2));
}

void Game::gameRestart()
{
	bricks.setupBricks();
}