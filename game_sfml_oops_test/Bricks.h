#pragma once
#include "common.h"
class Bricks
{
public:
	//Bricks(void);
	//Bricks(void);
	Bricks(sf::RenderWindow &myWindow);
	~Bricks(void);

	sf::RenderWindow &window;
	// Bricks
	sf::Texture tx[10];
	sf::Sprite sp[MAX_BRICKS];
	struct Brick
	{
		sf::Vector2f xy1 ; 
		sf::Vector2f xy2;
		Colors brickColor;
		sf::Sprite sp;
		bool display ;
		Brick()
		{
			xy1 = sf::Vector2f(0, 0); // brick default position
			xy2 = sf::Vector2f(0, 0); // brick default position
			display = true;
			brickColor = Colors::grey;
		}
	}bricksList[MAX_BRICKS];

	vector <string> imageNameSet;
	int imageCnt;
	int spriteCnt;
	// time based brick movement
	sf::Clock brickMoveTime;
	bool gameOver;
	int shooter_position ;
	int brickCount;

	void LoadBrickImages();
	void setupSprites(int l_x =10, int l_y =10);
	void setupBricks();
	void init();
	void draw();
	bool update();
	void updateBricksPosition();
	bool bulletHit(sf::Vector2f bulletPosion, sf::Vector2f bulletNextPosion, Colors bulletColor);
	void findSameColorNeighbors(int b_col , int b_row, set<int> &sameColorset);
	bool lineSegmentIntersction(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4);
	int getBrickCount(){return 	brickCount;}

};

