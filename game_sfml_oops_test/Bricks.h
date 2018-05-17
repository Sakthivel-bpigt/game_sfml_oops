#pragma once
#include "common.h"
class Bricks
{
public:
	//Bricks(void);
	//Bricks(void);
	Bricks(sf::RenderWindow &myWindow);
	~Bricks(void);

	sf::RenderWindow &window;
	// Bricks
	sf::Texture tx[10];
	sf::Sprite sp[100];
	struct Brick
	{
		sf::Vector2f xy1 ; 
		sf::Vector2f xy2;
		bool display ;
		Brick()
		{
			xy1 = sf::Vector2f(0, 0); // brick default position
			xy2 = sf::Vector2f(0, 0); // brick default position
			display = true;
		}
	}bricksList[100];

	vector <string> imageNameSet;
	int imageCnt;
	int spriteCnt;
	// time based brick movement
	sf::Clock brickMoveTime;
	bool gameOver;
	int shooter_position ;

	void LoadBrickImages();
	void setupSprites(int l_x =10, int l_y =10);
	void setupBricks();
	void init();
	void draw();
	bool update();
	void updateBricksPosition();

};

