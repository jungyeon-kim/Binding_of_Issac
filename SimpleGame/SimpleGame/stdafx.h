#pragma once

#include "targetver.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <tchar.h>
#include <math.h>
#include <iostream>
#include <memory>
#include <vector>

/*	--------------------------------------------
					custom area	бщ
	--------------------------------------------  */

#include "Vector.h"
#include "Color.h"
#include "Direction.h"

#define gameMgr GameMgr::getInstance()
#define gameCon GameController::getInstance()

constexpr float meter(float centiMeter = 1)
{
	return centiMeter * 100;
}

constexpr int wndSizeX{ static_cast<int>(meter(5)) };
constexpr int wndSizeY{ static_cast<int>(meter(5)) };

constexpr float gravity{ static_cast<float>(9.8) };