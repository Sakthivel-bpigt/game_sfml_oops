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

void Bricks::init()
{
	gameOver = false;
	shooter_position = SHOOTER_POSITION_Y;
	spriteCnt =100;

	setupSprites();
	setupBricks();
}

void Bricks::LoadBrickImages()
{
	//********************************************************************
	// This image array's elements order is in sync with the 'Colors' enum
	//********************************************************************

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
	for (int i = 0; i < ROW_BRICKS; i++)
	{
		for (int k = 0; k < COLUMN_BRICKS; k++)
		{
			int j = i*COLUMN_BRICKS+k;
			bricksList[j].brickColor = Colors(rand()%imageCnt);
			bricksList[j].sp.setTexture(tx[bricksList[j].brickColor]);
			//sp[cnt].setOrigin(sf::Vector2f(25, 25));
		}
	}
}

void Bricks::setupBricks()
{
	for (int i = 0; i < ROW_BRICKS; i++)
	{
		for (int k = 0; k < COLUMN_BRICKS; k++)
		{
			int j = i*COLUMN_BRICKS+k;
			// Setup the position of the brick
			bricksList[j].xy1 = sf::Vector2f(	BRICKS_AREA_START_X + (BRICKS_WIDTH*k),
													BRICKS_AREA_END_Y - (BRICKS_HEIGHT*(i+1)));
			bricksList[j].xy2 = sf::Vector2f(	BRICKS_AREA_START_X + (BRICKS_WIDTH*(k+1)),
													BRICKS_AREA_END_Y - (BRICKS_HEIGHT*i));
			
			// make the bottom five rows not active and used for wrong bullets that hit
			if(i <= 5) bricksList[j].display = false;
		}
	}
}

void Bricks::draw()
{
	for (int j = 0; j < MAX_BRICKS; j++)
	{
		if(bricksList[j].display)
		{
			bricksList[j].sp.setPosition(	bricksList[j].xy1);
			window.draw(bricksList[j].sp);
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
	if(brickMoveTime.getElapsedTime().asSeconds() < MOVE_BRICK_TIME) return;
	brickMoveTime.restart();
	for (int i = 0; i < ROW_BRICKS; i++)
	{
		for (int k = 0; k < COLUMN_BRICKS; k++)
		{
			int j = i*COLUMN_BRICKS+k;
			bricksList[j].xy1.y += BRICKS_MOVE_DIST;
			bricksList[j].xy2.y += BRICKS_MOVE_DIST;
			if(bricksList[j].xy2.y >= shooter_position)
				gameOver = true;
		}
	}
}

bool Bricks::bulletHit(sf::Vector2f bulletPosion, sf::Vector2f bulletNextPosion, Colors bulletColor)
{
	bool brickHit = false;
	int brickID = -1;
	int brick_col_ID = -1;
	int brick_row_ID = -1;
	sf::Vector2f p1 = bulletPosion;
	sf::Vector2f p2 =  bulletNextPosion;
	if(p1==p2) return brickHit;
	sf::Vector2f p3 = p1;
	sf::Vector2f p4 = p2;
	bool brickBottom, brickTop, brickLeft, brickRight;
	for (int i = 0; i < ROW_BRICKS; i++)
	{
		for (int k = 0; k < COLUMN_BRICKS; k++)
		{
			int j = i*COLUMN_BRICKS+k;
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

				if(brickBottom || brickLeft || brickRight)
				{
					if(brickBottom)
					{
						brick_col_ID = k;
						brick_row_ID = i-1;
					}else if(brickLeft)
					{
						brick_col_ID = k-1;
						brick_row_ID = i;
					}else if(brickRight)
					{
						brick_col_ID = k+1;
						brick_row_ID = i;
					}
					brickHit = true;
				//**********************************************
				// once found the first brick, exit the loops
				//**********************************************
					break;
				}
			}
		}
		//**********************************************
		// Once found the first brick, exit the loops
		//**********************************************
		if(brickHit) break;
	}
	if(brick_col_ID >= 0 && brick_row_ID >= 0)
	{
		//Add the brick in the appropriate place.
		int j = brick_row_ID*COLUMN_BRICKS+brick_col_ID;
		bricksList[j].brickColor = bulletColor;
		bricksList[j].sp.setTexture(tx[bricksList[j].brickColor]);
		bricksList[j].display = true;
		// FInd same colored bricks
		set<int> sameColorset;
		findSameColorNeighbors(brick_col_ID , brick_row_ID, sameColorset);
		if(sameColorset.size() >1)
			for (std::set<int>::iterator it=sameColorset.begin(); it!=sameColorset.end(); ++it)
				bricksList[*it].display = false;
	}
	return brickHit;
}
void Bricks::findSameColorNeighbors(int b_col , int b_row, set<int> &sameColorset)
{
	int j = b_row * COLUMN_BRICKS + b_col;
	Colors searchColor = bricksList[j].brickColor;

	std::pair<std::set<int>::iterator,bool> ret;

	ret = sameColorset.insert(j);
	if (ret.second == true)
	{
	// Left side
		if(b_col - 1 >=0)
		{
			int k = b_row * COLUMN_BRICKS + (b_col-1);
			if( bricksList[k].display && searchColor == bricksList[k].brickColor)
				findSameColorNeighbors(b_col-1 , b_row, sameColorset);
		}
	// right side
		if(b_col + 1 < COLUMN_BRICKS)
		{	
			int k = b_row * COLUMN_BRICKS + (b_col+1);
			if( bricksList[k].display && searchColor == bricksList[k].brickColor)
				findSameColorNeighbors(b_col+1 , b_row, sameColorset);
		}
	// top side
		if(b_row - 1 >=0)
		{	
			int k = (b_row-1) * COLUMN_BRICKS + b_col;
			if( bricksList[k].display && searchColor == bricksList[k].brickColor)
				findSameColorNeighbors(b_col , b_row-1 , sameColorset);
		}
	// right side
		if(b_row + 1 < ROW_BRICKS)
		{
			int k = (b_row+1) * COLUMN_BRICKS + b_col;
			if( bricksList[k].display && searchColor == bricksList[k].brickColor)
				findSameColorNeighbors(b_col , b_row+1, sameColorset);
		}
	}
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