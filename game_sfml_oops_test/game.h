#pragma once
#include "common.h"

class Game //:	public sf::RenderWindow
{
public:
	Game(void);
	~Game(void);
	void run();

private:
	// window
	sf::RenderWindow window;

// member functions
	void initialize();
};

