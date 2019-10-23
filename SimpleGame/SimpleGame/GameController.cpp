#include "stdafx.h"
#include "GameController.h"

using namespace std;

GameController* GameController::instance{};

GameController::GameController()
{
	init();
}

GameController::~GameController()
{
}

GameController* GameController::getInstance()
{
	if (!instance) instance = new GameController{};
	return instance;
}

void GameController::init()
{
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

void GameController::specialKeyDownInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		objShoot.up = true;
		break;
	case GLUT_KEY_DOWN:
		objShoot.down = true;
		break;
	case GLUT_KEY_LEFT:
		objShoot.left = true;
		break;
	case GLUT_KEY_RIGHT:
		objShoot.right = true;
		break;
	}
}

void GameController::specialKeyUpInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		objShoot.up = false;
		break;
	case GLUT_KEY_DOWN:
		objShoot.down = false;
		break;
	case GLUT_KEY_LEFT:
		objShoot.left = false;
		break;
	case GLUT_KEY_RIGHT:
		objShoot.right = false;
		break;
	}
}

bool GameController::isShoot() const
{
	return (objShoot.up || objShoot.down || objShoot.left || objShoot.right);
}

const Direction& GameController::getShoot() const
{
	return objShoot;
}

const Direction& GameController::getDir() const
{
	return objDir;
}