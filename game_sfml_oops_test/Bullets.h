#pragma once
#include "Bricks.h"
#define MAX_BULLETS 10
#define BULLET_SPEED 1
#define SHOOTER_POSITION_X 450
#define SHOOTER_POSITION_Y 470
class Bullet
{
public:
	sf::Sprite bulletSp;
	sf::Vector2f xy1 ; 
	sf::Vector2f direction;
	bool active ;
	float bulletSpeed;

	Bullet();
	~Bullet();
	void initi();
	void hitBrick(Bricks &bricks);
	void fly();
};
class Bullets
{
public:
	Bullets(sf::RenderWindow &myWindow, Bricks &bricks);
	~Bullets(void);

	sf::RenderWindow &window;
	Bricks &bricks;
	bool gameOver;

	// Shooter
	sf::Vector2f shooter_position;
	sf::Texture shooterTx;
	sf::Sprite shooterSp;

	//Bullets
	sf::Texture bulletTx;
	Bullet bulletList[MAX_BULLETS];
	sf::Clock NextBulletWaitTime;
	bool leftMouseClick;

	// Collision detection


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

