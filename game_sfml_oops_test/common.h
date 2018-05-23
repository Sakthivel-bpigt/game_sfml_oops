#pragma once
// program in C++
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace std;

#define WINDOW_ORIGIN 0
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 540

#define BRICKS_AREA_START_X 0
#define BRICKS_AREA_START_Y 0
#define BRICKS_AREA_END_X 850
#define BRICKS_AREA_END_Y 470

#define SHOOTER_POSITION_X 450
#define SHOOTER_POSITION_Y 470

#define MAX_BULLETS 10
#define BULLET_SPEED 1

#define EXPLOSION_TIME 0.2
#define NEXT_BULLET_TIME 0.2

#define PI 3.14159265

#define DEBUG 0

// try static window base class and
// inherite by others, so there'll be 
// one window for all
// Especially it'll help explosion class