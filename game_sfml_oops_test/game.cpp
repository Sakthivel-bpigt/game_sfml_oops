#include "game.h"


Game::Game(void)
	: bullets(bricks)
{
	initialize();
}


Game::~Game(void)
{
}

void Game::initialize()
{
	gWindow = GameWindow::getInstance();
	gWindow->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Brick shooter(pointer window)", sf::Style::Close);
	gWindow->setPosition(sf::Vector2i(WINDOW_ORIGIN_X, WINDOW_ORIGIN_Y));
	windowSp.loadSprite("background.jpg");
	gameOver = true;
	gameStart = false;
	setupPlayButton();
	setupGameOverButton();
	setupScoreDisplay();
}

bool Game::update()
{
	gWindow->clear();
	gWindow->draw(windowSp.get());

	return gameOver;
}
void Game::run()
{
	while (gWindow->isOpen())
    {
		sf::Event event;
        while (gWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gWindow->close();
        }

		gameOver = this->update();

		if(gameOver)
		{
			if(!gameStart)
			{
				gWindow->draw(playSp.get());
			}else
			{
				gWindow->draw(gameOverSp.get());
				updateScoreDisplay();
			}
			if (gameTime.getElapsedTime().asSeconds() > START_SHOOTER_TIME &&
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
			if (gameTime.getElapsedTime().asSeconds() > START_SHOOTER_TIME)
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

		gWindow->display();
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
	gWindow->draw(scoreText);
	gWindow->draw(bulletText);

	score = bricks.getBrickCount();
	scoreCountText.setString(to_string(score));
	gWindow->draw(scoreCountText);

	bulletCount = bullets.getBulletCount();
	bulletCountText.setString(to_string(bulletCount));
	gWindow->draw(bulletCountText);
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
