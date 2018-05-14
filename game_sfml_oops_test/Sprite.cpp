#include "Sprite.h"


Sprite::Sprite(void)
{
}

Sprite::Sprite(string str)
{loadSprite(str);}


Sprite::~Sprite(void)
{
}

void Sprite::loadSprite(string str)
{
	if (!Tx.loadFromFile(str.c_str()))
			cout<<" image loading error!";
	Sp.setTexture(Tx);
		//playgameSp.setOrigin(sf::Vector2f(316, 100));
}