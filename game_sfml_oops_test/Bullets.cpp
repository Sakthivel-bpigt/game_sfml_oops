#include "Bullets.h"


Bullets::Bullets(sf::RenderWindow &myWindow, Bricks &bricks)
	: window(myWindow)
	, bricks(bricks)
{
	gameOver = false;
	shooter_position = sf::Vector2f(SHOOTER_POSITION_X, SHOOTER_POSITION_Y);
	bulletSpeed = 1;
	leftMouseClick = false;

	//Functions
	setupSprites();
}

Bullets::~Bullets(void)
{
}

void Bullets::LoadImages()
{
	// 128 X 128
	if (!shooterTx.loadFromFile("png/shooter3.png"))
		std::cout<<" image loading error!";
	// 22 X 22
	if (!bulletTx.loadFromFile("png/ballBlue.png"))
		std::cout<<" image loading error!";
}
void Bullets::setupSprites()
{
	LoadImages();
	
	shooterSp.setTexture(shooterTx);
	shooterSp.setOrigin(sf::Vector2f(64, 64));

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bulletList[i].bulletSp.setTexture(bulletTx);
		bulletList[i].bulletSp.setOrigin(sf::Vector2f(11, 11));
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
		{
			bulletList[i].bulletSp.setPosition(bulletList[i].xy1);
			window.draw(bulletList[i].bulletSp);
		}
	}
}

bool Bullets::update()
{
	updateShooter();
	shootBullets();
	updateBullets();
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
			bulletList[i].xy1 += bulletList[i].direction * bulletSpeed;
		}
	}
	if(DEBUG)
	{
		//cout<< "V1 ("<<v1.x<<", "<<v1.y <<")  ";
		//cout<< v1.x*v2.x + v1.y*v2.y <<"  ";
		//cout<< -theta<<endl;
	}
}
void Bullets::shootBullets()
{
	leftMouseClick  = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (leftMouseClick)
	{
		// Check for waiting time
		if(NextBulletWaitTime.getElapsedTime().asSeconds() < 0.2) return;
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