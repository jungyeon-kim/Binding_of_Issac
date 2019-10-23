#include "stdafx.h"
#include "GameMgr.h"
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
	if (gameCon->isShoot())
		addObject(player->getPos(), { meter() / 4, meter() / 4, 0 }, { 1, 1, 1, 0 });

	for (const auto& i : bullet) i->update(eTime);
	player->update(eTime);
}

void GameMgr::render()
{
	renderer->render();
	for (const auto& i : bullet) i->render();
	player->render();
}

void GameMgr::addObject(const Vector& pos, const Vector& vol, const Color& col)
{
	if (bullet.size() < MAX_OBJECT)
	{
		bullet.emplace_back(make_unique<Bullet>());
		bullet.back()->setPos(pos);
		bullet.back()->setVol(vol);
		bullet.back()->setCol(col);
	}
	else 
		cout << "Object is full. \n";
}

void GameMgr::deleteObject()
{
	for (auto& i = bullet.cbegin(); i != bullet.cend();)
	{
		if (i->get()->getPos().x > meter()) i = bullet.erase(i);
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
