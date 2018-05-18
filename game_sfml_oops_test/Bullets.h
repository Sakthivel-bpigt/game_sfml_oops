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
		sf::Vector2f direction;
		bool active ;
		Bullet()
		{
			xy1 = sf::Vector2f(SHOOTER_POSITION_X, SHOOTER_POSITION_Y); // Bullet default position
			direction = sf::Vector2f(0, 0); // Bullet default direction
			active = false;
		}
	}bulletList[MAX_BULLETS];
	sf::Clock NextBulletWaitTime;
	float bulletSpeed;
	bool leftMouseClick;


	// Member Functions
	void LoadImages();
	void setupSprites();
	void draw();
	bool update();
	void updateShooter();
	void updateBullets();
	void shootBullets();
	sf::Vector2f calcUnitVector(sf::Vector2f p1, sf::Vector2f p2);

};

