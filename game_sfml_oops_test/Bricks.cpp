#include "Bricks.h"


Bricks::Bricks(void)
{
	init();
	LoadBrickImages();
	setupSprites();
	setupBricks();
}

//Bricks::Bricks(sf::RenderWindow &myWindow)
//{
//	window = myWindow;
//	init();
//}


Bricks::~Bricks(void)
{
}

void Bricks::LoadBrickImages()
{
	for (int i = 0; i < imageCnt; i++)
	{
		if (!tx[i].loadFromFile(imageNameSet[i].c_str()))
		std::cout<<" image loading error!";
	}
}
void Bricks::setupSprites(int l_x, int l_y)
{
	LoadBrickImages();
	for (int i = 0; i < l_y; i++)
	{
		for (int j = 0; j < l_x; j++)
		{
			sp[i*10+j].setTexture(tx[rand()%imageCnt]);
			//sp[cnt].setOrigin(sf::Vector2f(25, 25));
		}
	}
}
void Bricks::setupBricks()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			bricksList[i*10+j].xy1 = sf::Vector2f(100+(70*j), -315+(40*i));
			bricksList[i*10+j].xy2 = sf::Vector2f(100+(70*(j+1)), -315+(40*(i+1)));
		}
	}
}

void Bricks::init()
{
	imageNameSet.push_back("png/element_blue_rectangle_glossy.png");
	imageNameSet.push_back("png/element_red_rectangle_glossy.png");
	imageNameSet.push_back("png/element_grey_rectangle_glossy.png");
	imageNameSet.push_back("png/element_purple_rectangle_glossy.png");
	imageNameSet.push_back("png/element_yellow_rectangle_glossy.png");
	imageNameSet.push_back("png/element_green_rectangle_glossy.png");

	imageCnt = imageNameSet.size();
		spriteCnt =100;
}

void Bricks::draw(sf::RenderWindow &window)
{
	for (int j = 0; j < 100; j++)
	{
		if(bricksList[j].display)
		{
			sp[j].setPosition(	bricksList[j].xy1);
			window.draw(sp[j]);
		}
	}
}