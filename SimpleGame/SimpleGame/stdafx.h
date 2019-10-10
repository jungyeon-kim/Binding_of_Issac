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

constexpr float meter(float cMeter = 1)
{
	return cMeter * 100;
}

constexpr float wndSizeX{ meter(5) };
constexpr float wndSizeY{ meter(5) };