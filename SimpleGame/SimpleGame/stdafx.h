#pragma once

#define _USE_MATH_DEFINES

#include "targetver.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <tchar.h>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <random>
#include <chrono>
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

#include "Vector.h"
#include "Color.h"
#include "Direction.h"
#include "Enum.h"

#define gameMgr GameMgr::getInstance()
#define gameCon GameController::getInstance()
#define objMgr ObjMgr::getInstance()
#define scnMgr ScnMgr::getInstance()
#define texMgr TexMgr::getInstance()
#define renderer Renderer::getInstance()

constexpr float meter(float centiMeter = 1.0f)
{
	return centiMeter * 100.0f;
}

constexpr float angle(float val)
{
	return val * static_cast<float>(M_PI) / 180.0f;
}

constexpr unsigned int hashCode(const char *str)
{
	unsigned int hash{};
	while (*str)
	{
		hash = 65599 * hash + str[0];
		++str;
	}
	return hash ^ (hash >> 16);
}

constexpr int wndSizeX{ static_cast<int>(meter(19.0f)) };
constexpr int wndSizeY{ static_cast<int>(meter(9.0f)) };

constexpr float gravity{ static_cast<float>(9.8f) };
constexpr int frame{ 8 };