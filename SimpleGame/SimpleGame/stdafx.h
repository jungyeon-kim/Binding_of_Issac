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
#include <array>
#include <vector>
#include <map>
#include <unordered_map>

/*	--------------------------------------------
					custom area	бщ
	--------------------------------------------  */

#include "Vector.h"
#include "Color.h"
#include "Direction.h"

enum class Tex { TEST, ISAC_HEAD, ISAC_BODY, BASIC_BULLET };
enum class Obj { BLOCK_BOX, PORTAL_BOX, PLAYER, ENEMY, BULLET };

constexpr float meter(float centiMeter = 1)
{
	return centiMeter * 100;
}

constexpr int frame{ 8 };

constexpr int wndSizeX{ static_cast<int>(meter(19.0f)) };
constexpr int wndSizeY{ static_cast<int>(meter(9.0f)) };

constexpr float gravity{ static_cast<float>(9.8f) };