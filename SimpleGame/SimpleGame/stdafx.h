#pragma once

#include "targetver.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <tchar.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <memory>
#include <map>
#include <unordered_map>

/*	--------------------------------------------
					custom area	бщ
	--------------------------------------------  */

#include "Vector.h"
#include "Color.h"
#include "Direction.h"

#define PLAYER dynamic_cast<Player*>(obj->find("Player")->second.get())

constexpr float meter(float centiMeter = 1)
{
	return centiMeter * 100;
}

constexpr int wndSizeX{ static_cast<int>(meter(19.20)) };
constexpr int wndSizeY{ static_cast<int>(meter(10.80)) };

constexpr float gravity{ static_cast<float>(9.8) };