#pragma once
#include "common.h"
#include "Sprite.h"

class Game //:	public sf::RenderWindow
{
public:
	Game(void);
	~Game(void);
	void run();

private:
	// window
	sf::RenderWindow window;
	Sprite windowSp;
// member functions
	void initialize();
};

