#include "Explosion.h"


Explosion::Explosion(void)
{
	initi();
}


Explosion::~Explosion(void)
{
}

void Explosion::initi()
{
	gWindow = GameWindow::getInstance();
	xy1 = sf::Vector2f(SHOOTER_POSITION_X, SHOOTER_POSITION_Y); // Bullet default position
	active = false;
	//life = EXPLOSION_TIME;
}

void Explosion::setSprite(sf::Texture &explosionTx, sf::Vector2f pos)
{
	explosionSp.setTexture(explosionTx);
	explosionSp.setOrigin(pos);
}

void Explosion::setExplode(sf::Vector2f position)
{
	active = true;
	xy1 = position;
	life.restart();
	explosionSp.setRotation(rand()%360); // absolute angle
}

void Explosion::update()
{
	// Check for waiting time
	if(life.getElapsedTime().asSeconds() > EXPLOSION_TIME) 
	{
		active = false;
	}
}

void Explosion::draw(sf::RenderWindow &myWindow)
{
	explosionSp.setPosition(xy1);
	myWindow.draw(explosionSp);
}

void Explosion::draw()
{
	explosionSp.setPosition(xy1);
	gWindow->draw(explosionSp);
}