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
	Sprite windowSp;
	Explosion explode;
	Bullets bullet;
// member functions
	void initialize();
};

