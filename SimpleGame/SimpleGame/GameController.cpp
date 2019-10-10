#include "stdafx.h"
#include "GameController.h"

using namespace std;

GameController* GameController::instance{};

GameController::GameController()
{
}

GameController::~GameController()
{
}

GameController* GameController::getInstance()
{
	if (!instance) instance = new GameController{};
	return instance;
}

void GameController::keyDownInput(unsigned char key, int x, int y)
{
	switch (key | 32)
	{
	case 'w':
		objDir.up = true;
		break;
	case 'a':
		objDir.left = true;
		break;
	case 's':
		objDir.down = true;
		break;
	case 'd':
		objDir.right = true;
		break;
	}
}

void GameController::keyUpInput(unsigned char key, int x, int y)
{
	switch (key | 32)
	{
	case 'w':
		objDir.up = false;
		break;
	case 'a':
		objDir.left = false;
		break;
	case 's':
		objDir.down = false;
		break;
	case 'd':
		objDir.right = false;
		break;
	}
}

const Direction& GameController::getDir() const
{
	return objDir;
}

void GameController::setDir(const Direction& dir)
{
	objDir = dir;
}
