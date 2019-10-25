#include "stdafx.h"
#include "GameMgr.h"
#include "GameMgr.hpp"
#include "Renderer.h"
#include "GameController.h"
#include "Player.h"
#include "Bullet.h"

using namespace std;

GameMgr* GameMgr::instance{};

GameMgr::GameMgr()
{
	init();
}

GameMgr::~GameMgr()
{
}

void GameMgr::garbageCollect()
{
	// delete bullet
	deleteObject();
}

GameMgr* GameMgr::getInstance()
{
	if (!instance) instance = new GameMgr{};
	return instance;
}

void GameMgr::init()
{
	renderer = make_unique<Renderer>(wndSizeX, wndSizeY);
	if (!renderer->IsInitialized()) { cout << "Renderer could not be initialized.. \n"; }
	gameCon = GameController::getInstance();
	player = make_unique<Player>();
}

void GameMgr::update(float eTime)
{
	if (gameCon->isShoot()) addObject<Bullet>("Bullet");
	deleteObject();

	for (const auto& i : bullet) i->update(eTime);
	player->update(eTime);
}

void GameMgr::render()
{
	renderer->render();
	for (const auto& i : bullet) i->render();
	player->render();
}

void GameMgr::deleteObject()
{
	for (auto& i = bullet.cbegin(); i != bullet.cend();)
	{
		if (sqrtf(pow(i->get()->getVel().x, 2) + 
			pow(i->get()->getVel().y, 2) + 
			pow(i->get()->getVel().z, 2)) == 0) 
			i = bullet.erase(i);
		else ++i;
	}
}

void GameMgr::keyDownInput(unsigned char key, int x, int y)
{
	gameCon->keyDownInput(key, x, y);
}

void GameMgr::keyUpInput(unsigned char key, int x, int y)
{
	gameCon->keyUpInput(key, x, y);
}

void GameMgr::specialKeyDownInput(int key, int x, int y)
{
	gameCon->specialKeyDownInput(key, x, y);
}

void GameMgr::specialKeyUpInput(int key, int x, int y)
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
