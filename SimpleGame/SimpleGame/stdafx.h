#pragma once

#include "targetver.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <tchar.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <algorithm>
#include <map>
#include <unordered_map>

/*	--------------------------------------------
					custom area	бщ
	--------------------------------------------  */

#include "Vector.h"
#include "Color.h"
#include "Direction.h"

enum class Obj { PLAYER, PLAYER_BULLET, ENEMY_BULLET };
enum class Skill { SHOOT };

constexpr float meter(float centiMeter = 1)
{
	return centiMeter * 100;
}

constexpr int frame{ 8 };

constexpr int wndSizeX{ static_cast<int>(meter(19.20f)) };
constexpr int wndSizeY{ static_cast<int>(meter(10.80f)) };

constexpr float gravity{ static_cast<float>(9.8f) };