#include "Bricks.h"


//Bricks::Bricks(void):window(NULL)
//{
////	window = NULL;
//}

Bricks::Bricks(sf::RenderWindow &myWindow):window(myWindow)
{
	init();
}

Bricks::~Bricks(void)
{
}

void Bricks::LoadBrickImages()
{
	imageNameSet.push_back("png/element_blue_rectangle_glossy.png");
	imageNameSet.push_back("png/element_red_rectangle_glossy.png");
	imageNameSet.push_back("png/element_grey_rectangle_glossy.png");
	imageNameSet.push_back("png/element_purple_rectangle_glossy.png");
	imageNameSet.push_back("png/element_yellow_rectangle_glossy.png");
	imageNameSet.push_back("png/element_green_rectangle_glossy.png");

	imageCnt = imageNameSet.size();

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
	gameOver = false;
	shooter_position = 470;
	spriteCnt =100;

	setupSprites();
	setupBricks();
}

void Bricks::draw()
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

bool Bricks::update()
{
	draw();
	// stop moving bricks when game is over
	if(!gameOver) 
		updateBricksPosition();
	return gameOver;
}

void Bricks::updateBricksPosition()
{
	if(brickMoveTime.getElapsedTime().asSeconds() < 0.5) return;
	brickMoveTime.restart();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			bricksList[i*10+j].xy1.y += 10;
			bricksList[i*10+j].xy2.y += 10;
			if(bricksList[i*10+j].xy2.y >= shooter_position)
				gameOver = true;
		}
	}
}

bool Bricks::bulletHit(sf::Vector2f bulletPosion, sf::Vector2f bulletNextPosion)
{
	bool brickHit = false;
	int brickID = -1;
	sf::Vector2f p1 = bulletPosion;
	sf::Vector2f p2 =  bulletNextPosion;
	if(p1==p2) return brickHit;
	sf::Vector2f p3 = p1;
	sf::Vector2f p4 = p2;
	bool brickBottom, brickTop, brickLeft, brickRight;
	for (int j = 0; j < MAX_BRICKS; j++)
	{
		if(bricksList[j].display)
		{
			p3 = bricksList[j].xy1;
			p4 = sf::Vector2f(bricksList[j].xy2.x, bricksList[j].xy1.y);
			brickTop = lineSegmentIntersction(p1, p2, p3, p4);

			p3 = sf::Vector2f(bricksList[j].xy1.x, bricksList[j].xy2.y);
			p4 = bricksList[j].xy2;
			brickBottom = lineSegmentIntersction(p1, p2, p3, p4);

			p3 = bricksList[j].xy1;
			p4 = sf::Vector2f(bricksList[j].xy1.x, bricksList[j].xy2.y);
			brickLeft = lineSegmentIntersction(p1, p2, p3, p4);

			p3 = sf::Vector2f(bricksList[j].xy2.x, bricksList[j].xy1.y);
			p4 = bricksList[j].xy2;
			brickRight = lineSegmentIntersction(p1, p2, p3, p4);

			if(brickBottom || brickTop || brickLeft || brickRight)
				brickID = j;
		}
	}
	if(brickID>=0)
	{
		bricksList[brickID].display = false;
		brickHit = true;
	}
	return brickHit;
}

bool Bricks::lineSegmentIntersction(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4)
{
	float ta =	((p3.y - p4.y)*(p1.x-p3.x)+(p4.x-p3.x)*(p1.y-p3.y))/
				((p4.x-p3.x)*(p1.y - p2.y) - (p1.x-p2.x)*(p4.y-p3.y));
	float tb =	((p1.y-p2.y)*(p1.x-p3.x) + (p2.x-p1.x)*(p1.y-p3.y))/
				((p4.x-p3.x)*(p1.y - p2.y) - (p1.x-p2.x)*(p4.y-p3.y));

	bool result = false;
	if(ta>=0 && ta<=1 && tb>=0 && tb<=1)
		result = true;
	return result;
}