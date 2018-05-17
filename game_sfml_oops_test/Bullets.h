#pragma once
#include "Bricks.h"
#define MAX_BULLETS 10
#define SHOOTER_POSITION_X 450
#define SHOOTER_POSITION_Y 470
class Bullets
{
public:
	Bullets(sf::RenderWindow &myWindow, Bricks &bricks);
	~Bullets(void);

	sf::RenderWindow &window;
	Bricks &bricks;

	bool gameOver;
	sf::Vector2f shooter_position;
	// Shooter
	sf::Texture shooterTx;
	sf::Sprite shooterSp;

	//Bullets
	sf::Texture bulletTx;
	struct Bullet
	{
		sf::Sprite bulletSp;
		sf::Vector2f xy1 ; 
		//sf::Vector2f xy2;
		bool display ;
		Bullet()
		{
			xy1 = sf::Vector2f(0, 0); // brick default position
			//xy2 = sf::Vector2f(0, 0); // brick default position
			display = true;
		}
	}bulletList[MAX_BULLETS];


	// Member Functions
	void LoadImages();
	void setupSprites();
	void draw();
	bool update();
};

