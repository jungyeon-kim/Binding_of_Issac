#include "stdafx.h"		
#include "GameMgr.h"
#include "Renderer.h"
#include "Physics.h"
#include "GameController.h"
#include "ObjectSet.h"

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
	physics = make_unique<Physics>();
	gameCon = GameController::getInstance();
	obj = make_unique<unordered_multimap<Obj, unique_ptr<GameObj>>>();

	addObject<Player>(Obj::PLAYER, { 0.0f, 0.0f, 0.0f });
}

void GameMgr::update(float eTime)
{
	if (obj->find(Obj::PLAYER) != obj->end())
	{
		static const auto& player{ getObj<Player>(Obj::PLAYER) };

		if (gameCon->isShoot() && player->isEndCoolTime(Skill::SHOOT))
		{
			addObject<Bullet>(Obj::BULLET, player->getPos(), player->getVel());
			player->resetCoolTime(Skill::SHOOT);
		}
	}

	garbageCollect();

	for (const auto& obj : *obj) obj.second->update(eTime);
}

void GameMgr::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.5f, 0.5f, 1.0f);

	for (const auto& obj : *obj) obj.second->render();
}

void GameMgr::deleteObject(Obj name)
{
	const auto& target{ obj->find(name) };

	if (target != obj->end()) obj->erase(target);
	else cout << "Cannot delete. " << static_cast<int>(name) << " Object is not exist. \n";
}

void GameMgr::garbageCollect()
{
	for (auto& i = obj->begin(); i != obj->end();)
		switch (i->first)
		{
		case Obj::PLAYER:
			++i;
			break;
		case Obj::BULLET:
			if (!physics->calcScalar(i->second->getVel())) i = obj->erase(i);
			else ++i;
			break;
		}
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
