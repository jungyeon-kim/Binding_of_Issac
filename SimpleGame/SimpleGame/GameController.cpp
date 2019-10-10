#include "stdafx.h"
#include "GameController.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::keyDownInput(unsigned char key, int x, int y)
{
	switch (key | 32)
	{
	case 'w':
		keyW = true;
		break;
	case 'a':
		keyA = true;
		break;
	case 's':
		keyS = true;
		break;
	case 'd':
		keyD = true;
		break;
	}
}

void GameController::keyUpInput(unsigned char key, int x, int y)
{
	switch (key | 32)
	{
	case 'w':
		keyW = false;
		break;
	case 'a':
		keyA = false;
		break;
	case 's':
		keyS = false;
		break;
	case 'd':
		keyD = false;
		break;
	}
}
