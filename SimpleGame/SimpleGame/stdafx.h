#pragma once

#include "targetver.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <tchar.h>
#include <math.h>
#include <assert.h>

#include <iostream>
#include <cstdlib>
#include <random>
#include <fstream>
#include <memory>
#include <algorithm>
#include <iterator>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>

/*	--------------------------------------------
					custom area	бщ
	--------------------------------------------  */

#define gameMgr GameMgr::getInstance()
#define gameCon GameController::getInstance()
#define objMgr ObjMgr::getInstance()
#define scnMgr ScnMgr::getInstance()
#define texMgr TexMgr::getInstance()

#include "Vector.h"
#include "Color.h"
#include "Direction.h"

enum class Tex { TEST, BACK_GROUND, ISAC_HEAD, ISAC_BODY, BASIC_BULLET };
enum class Obj { NONE, BLOCK_BOX, PORTAL_BOX, PLAYER, ENEMY, PLAYER_BULLET, ENEMY_BULLET };

constexpr float meter(float centiMeter = 1)
{
	return centiMeter * 100;
}

constexpr int frame{ 8 };

constexpr int wndSizeX{ static_cast<int>(meter(19.0f)) };
constexpr int wndSizeY{ static_cast<int>(meter(9.0f)) };

constexpr float gravity{ static_cast<float>(9.8f) };