#include "stdafx.h"		
#include "GameMgr.h"
#include "ObjMgr.h"
#include "ScnMgr.h"
#include "GameController.h"

using namespace std;

GameMgr* GameMgr::instance{};

GameMgr::GameMgr()
{
	init();
}

GameMgr::~GameMgr()
{
}

GameMgr* GameMgr::getInstance()
{
	if (!instance) instance = new GameMgr{};
	return instance;
}

void GameMgr::init()
{
}

void GameMgr::update(float eTime)
{
	objMgr->update(eTime);
}

void GameMgr::render()
{
	scnMgr->render();
	objMgr->render();
}

void GameMgr::keyDownInput(unsigned char key, int x, int y) const
{
	gameCon->keyDownInput(key, x, y);
}

void GameMgr::keyUpInput(unsigned char key, int x, int y) const
{
	gameCon->keyUpInput(key, x, y);
}

void GameMgr::specialKeyDownInput(int key, int x, int y) const
{
	gameCon->specialKeyDownInput(key, x, y);
}

void GameMgr::specialKeyUpInput(int key, int x, int y) const
{
	gameCon->specialKeyUpInput(key, x, y);
}

int GameMgr::getElapsedTime()
{
	currTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currTime - prevTime;
	prevTime = currTime;
	//cout << "elapsed time (ms): " << elapsedTime << endl;

	return elapsedTime;
}