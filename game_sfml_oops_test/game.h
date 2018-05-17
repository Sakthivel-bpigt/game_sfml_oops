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
	Explosion explode;
	bool gameOver;
// member functions
	void initialize();
	bool update();
};

