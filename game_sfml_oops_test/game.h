#pragma once
#include "common.h"
#include "Sprite.h"
#include "Bricks.h"
#include "Explosion.h"
#include "Bullets.h"

class Game //:	public sf::RenderWindow
{
public:
	Game(void);
	~Game(void);
	void run();

private:
	// window
	sf::RenderWindow gameWindow;
	Bricks bricks;
	Bullets bullets;
	Sprite windowSp;
	Sprite playSp;
	Sprite gameOverSp;
	Explosion explode;
	bool gameOver;
	bool gameStart;
	sf::Clock gameTime;




// member functions
	void initialize();
	bool update();
	void setupPlayButton();
	void setupGameOverButton();
	void gameRestart();
};

