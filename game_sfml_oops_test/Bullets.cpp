#include "Bullets.h"


Bullets::Bullets(sf::RenderWindow &myWindow, Bricks &bricks)
	: window(myWindow)
	, bricks(bricks)
{
	gameOver = false;
	shooter_position = sf::Vector2f(SHOOTER_POSITION_X, SHOOTER_POSITION_Y);
	//bulletSpeed = 1;
	leftMouseClick = false;

	//Functions
	LoadImages();
	
	shooterSp.setTexture(shooterTx);
	shooterSp.setOrigin(sf::Vector2f(64, 64));

	setupBullets();
	setupExplosions();
}

Bullets::~Bullets(void)
{
}

void Bullets::LoadImages()
{
	//// 225 X 225
	//if (!shooterTx.loadFromFile("png/shooter4.png"))
	//	std::cout<<" image loading error!";

	// 128 X 128
	if (!shooterTx.loadFromFile("png/shooter3.png"))
		std::cout<<" image loading error!";

	// 22 X 22
	if (!bulletTx.loadFromFile("png/ballBlue.png"))
		std::cout<<" image loading error!";

	// 128 X 128
	if (!explosionTx.loadFromFile("png/explosion.png"))
		std::cout<<" image loading error!";
}
void Bullets::setupBullets()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bulletList[i].setSprite(bulletTx, sf::Vector2f(11, 11));
	}
}

void Bullets::setupExplosions()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		//explosionList[i].pWindow = &window;
		explosionList[i].setSprite(explosionTx, sf::Vector2f(64, 64));
	}
}

void Bullets::draw()
{
	shooterSp.setPosition(shooter_position);
//	shooterSp.setRotation(-90); // absolute angle
	window.draw(shooterSp);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if(bulletList[i].active)
			bulletList[i].draw(window);

		if(explosionList[i].active)
			explosionList[i].draw(window);
	}
}

bool Bullets::update()
{
	updateShooter();
	shootBullets();
	updateBullets();
	updateExplosions();
	draw();
	// stop moving bricks when game is over
	/*if(!gameOver) 
		updateBricksPosition();*/
	return gameOver;
}

void Bullets::updateShooter()
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

	sf::Vector2f v1 = calcUnitVector(shooter_position, mousePosition);
	sf::Vector2f v2 = sf::Vector2f (1,0.0000001);
	//Finding the Angle Between Two Vectors
	float theta = acosf(v1.x*v2.x + v1.y*v2.y ) * 180.0 / PI;
	shooterSp.setRotation( -theta); // absolute angle
	
	if(DEBUG)
	{
		cout<< "V1 ("<<v1.x<<", "<<v1.y <<")  ";
		cout<< v1.x*v2.x + v1.y*v2.y <<"  ";
		cout<< -theta<<endl;
	}
}
sf::Vector2f Bullets::calcUnitVector(sf::Vector2f p1, sf::Vector2f p2)
{
	sf::Vector2f diffPos = (p2 - p1);
	float diffLength = sqrtf(diffPos.x * diffPos.x + diffPos.y * diffPos.y);
	float diffNorm = 1/diffLength;
	return diffPos * diffNorm;
}

void Bullets::updateBullets()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if(bulletList[i].active)
		{
			bulletList[i].fly();
			bool collision = bulletList[i].hitBrick(bricks, explosionList);
		}
	}
	if(DEBUG)
	{
		//cout<< "V1 ("<<v1.x<<", "<<v1.y <<")  ";
		//cout<< v1.x*v2.x + v1.y*v2.y <<"  ";
		//cout<< -theta<<endl;
	}
}

void Bullets::updateExplosions()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		explosionList[i].update();
	}
}

void Bullets::shootBullets()
{
	leftMouseClick  = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (leftMouseClick)
	{
		// Check for waiting time
		if(NextBulletWaitTime.getElapsedTime().asSeconds() < NEXT_BULLET_TIME) return;
		NextBulletWaitTime.restart();
		
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if(!bulletList[i].active)
			{
				bulletList[i].active = true;
				bulletList[i].direction = calcUnitVector(shooter_position, mousePosition);
				leftMouseClick = false;
				break;
			}
		}
	}
}
Bullet::Bullet()
{
	initi();
}
Bullet::~Bullet()
{
}
void Bullet::initi()
{
	xy1 = sf::Vector2f(SHOOTER_POSITION_X, SHOOTER_POSITION_Y); // Bullet default position
	direction = sf::Vector2f(0, 0); // Bullet default direction
	active = false;
	bulletSpeed = BULLET_SPEED;
}
bool Bullet::hitBrick(Bricks &bricks, Explosion *pExplosionList)
{
	bool hitSomething = false;
	if(active)
	{
		sf::Vector2f p1 = xy1;
		sf::Vector2f p2 = xy1 + direction * bulletSpeed;
		hitSomething = bricks.bulletHit(p1,p2);
		if(hitSomething)
		{
			// setting explosion
			
			for (int j = 0; j < MAX_BULLETS; j++)
			{
				if(!pExplosionList[j].active)
				{
					pExplosionList[j].setExplode(xy1);
					break;
				}
			}

			initi();
		}else
		{
			// Deactivate the bullet if it goes out of the play area (window)
			if(xy1.x < WINDOW_ORIGIN || 
				xy1.x > WINDOW_WIDTH || 
				xy1.y < WINDOW_ORIGIN || 
				xy1.y > WINDOW_HEIGHT  )
				initi();
		}
	}
	return hitSomething;
}
void Bullet::fly()
{
	xy1 += direction * bulletSpeed;
}

void Bullet::setSprite(sf::Texture &bulletTx, sf::Vector2f pos)
{
	bulletSp.setTexture(bulletTx);
	bulletSp.setOrigin(pos);
}
void Bullet::draw(sf::RenderWindow &myWindow)
{
	bulletSp.setPosition(xy1);
	myWindow.draw(bulletSp);
}