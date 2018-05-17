#include "Bullets.h"


Bullets::Bullets(sf::RenderWindow &myWindow, Bricks &bricks)
	: window(myWindow)
	, bricks(bricks)
{
	gameOver = false;
	shooter_position = sf::Vector2f(SHOOTER_POSITION_X, SHOOTER_POSITION_Y);

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
	shooterSp.setRotation(-90); // absolute angle
	window.draw(shooterSp);
	//for (int j = 0; j < 100; j++)
	//{
	//	if(bricksList[j].display)
	//	{
	//		sp[j].setPosition(	bricksList[j].xy1);
	//		window.draw(sp[j]);
	//	}
	//}
}

bool Bullets::update()
{
	draw();
	// stop moving bricks when game is over
	/*if(!gameOver) 
		updateBricksPosition();*/
	return gameOver;
}