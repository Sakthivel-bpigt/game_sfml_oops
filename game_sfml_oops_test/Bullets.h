#pragma once
#include "Bricks.h"
#include "Explosion.h"

//#define SHOOTER_POSITION_X 450
//#define SHOOTER_POSITION_Y 470
class Bullet
{
public:
	sf::Sprite bulletSp;		// bullet image
	sf::Vector2f xy1 ;			// bullet position
	sf::Vector2f direction;		// bullet direction
	bool active ;				// is bullet alive
	float bulletSpeed;			// bullet travelling speed

	Bullet();
	~Bullet();
	void initi();
	bool hitBrick(Bricks &bricks, Explosion *pExplosionList);
	void fly();
	void setSprite(sf::Texture &bulletTx, sf::Vector2f pos);
	void draw(sf::RenderWindow &myWindow);
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
	vector <string> imageNameSet;
	int imageCnt;
	sf::Texture tx[10];
	sf::Texture bulletTx;
	Bullet bulletList[MAX_BULLETS];
	sf::Clock NextBulletWaitTime;
	bool leftMouseClick;
	int nextBulletColor;
	Bullet nextBullet;
	// Collision 
	sf::Texture explosionTx;
	Explosion explosionList[MAX_BULLETS];

	// Member Functions
	void LoadImages();
	void setupBullets();
	void setupExplosions();
	void draw();
	bool update();
	void updateShooter();
	void updateBullets();
	void updateExplosions();
	void shootBullets();
	void chooseNextBulletColor();
	void setupNextBullet();
	void updateNextBullet();
	void drawNextBullet();

	int randomNumberGen(int limit){return rand() % limit;};
	sf::Vector2f calcUnitVector(sf::Vector2f p1, sf::Vector2f p2);
};

