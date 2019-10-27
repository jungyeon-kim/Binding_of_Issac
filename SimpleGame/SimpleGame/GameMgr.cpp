#include "stdafx.h"		
#include "GameMgr.h"
#include "Renderer.h"
#include "Physics.h"
#include "GameController.h"
#include "GameObj.h"
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

void GameMgr::deleteObject()
{
	for (auto& i = obj->cbegin(); i != obj->cend();)
	{
		if (i->first == "Bullet" && !physics->calcScalar(i->second->getVel())) 
			i = obj->erase(i);
		else 
			++i;
	}
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
	physics = make_unique<Physics>();
	gameCon = GameController::getInstance();
	obj = make_unique<unordered_multimap<string, unique_ptr<GameObj>>>();

	addObject<Player>("Player");
}

void GameMgr::update(float eTime)
{
	if (gameCon->isShoot()) addObject<Bullet>("Bullet");
	garbageCollect();

	for (const auto& obj : *obj) obj.second->update(eTime);
}

void GameMgr::render()
{
	renderer->render();
	for (const auto& obj : *obj) obj.second->render();
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
