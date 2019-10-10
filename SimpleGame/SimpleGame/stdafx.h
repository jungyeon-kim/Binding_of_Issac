#pragma once

#include "targetver.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <iostream>
#include <tchar.h>
#include <memory>
#include <vector>

/*	--------------------------------------------
					custom area	бщ
	--------------------------------------------  */

#include "Vector.h"
#include "Color.h"
#include "Direction.h"

constexpr float meter(float cMeter = 1)
{
	return cMeter * 100;
}

constexpr int wndSizeX{ static_cast<int>(meter(5)) };
constexpr int wndSizeY{ static_cast<int>(meter(5)) };