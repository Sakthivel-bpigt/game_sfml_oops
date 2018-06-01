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
	 gameWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Brick shooter", sf::Style::Close);
	 windowSp.loadSprite("background.jpg");
	gameOver = true;
	gameStart = false;
	 setupPlayButton();
	 setupGameOverButton();
	 setupScoreDisplay();
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
				updateScoreDisplay();
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
			updateScoreDisplay();

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
	bullets.reset();
}

void Game::setupScoreDisplay()
{
	score = 0;
	bulletCount = 0;
	// select the font
	font_arial.loadFromFile("font/ARLRDBD.ttf");
	font_gothic.loadFromFile("font/SHOWG.ttf");

	setupText(scoreText, font_gothic, "Score");
	setupText(scoreCountText, font_arial, to_string(score));
	setupText(bulletText, font_gothic, "Bullets");
	setupText(bulletCountText, font_arial, to_string(bulletCount));

	// set positions
	scoreText.setPosition(sf::Vector2f(SCORE_POSITION_X, SCORE_POSITION_Y));
	scoreCountText.setPosition(sf::Vector2f(SCORE_POSITION_X + 150, SCORE_POSITION_Y));

	// set positions
	bulletText.setPosition(sf::Vector2f(BULLET_CNT_POSITION_X, BULLET_CNT_POSITION_Y));
	bulletCountText.setPosition(sf::Vector2f(BULLET_CNT_POSITION_X + 200, BULLET_CNT_POSITION_Y));
}

void Game::updateScoreDisplay()
{
	gameWindow.draw(scoreText);
	gameWindow.draw(bulletText);

	score = bricks.getBrickCount();
	scoreCountText.setString(to_string(score));
	gameWindow.draw(scoreCountText);

	bulletCount = bullets.getBulletCount();
	bulletCountText.setString(to_string(bulletCount));
	gameWindow.draw(bulletCountText);
}

void Game::setupText(sf::Text &text, sf::Font &font, sf::String str)
{
	//sf::Text text;
	text.setFont(font); // font is a sf::Font
	//scoreText.setFont(font_arial); // font is a sf::Font

	// set the string to display
	text.setString(str);
	//scoreText.setString(to_string(score));

	// set the character size
	text.setCharacterSize(34); // in pixels, not points!
	//scoreText.setCharacterSize(34); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::Blue);
	//scoreText.setFillColor(sf::Color::Magenta);

	// set the text style
	text.setStyle(sf::Text::Bold );//| sf::Text::Underlined);
	//scoreText.setStyle(sf::Text::Italic );//| sf::Text::Underlined);
}
