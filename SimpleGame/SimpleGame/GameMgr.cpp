#include "stdafx.h"
#include "GameMgr.h"
#include "Renderer.h"
#include "GameObj.h"
#include "Player.h"

using namespace std;

GameMgr* GameMgr::instance{};

GameMgr::GameMgr()
{
	gameController = GameController::getInstance();
	player = make_unique<Player>();
}

GameMgr::~GameMgr()
{
}

GameMgr* GameMgr::getInstance()
{
	if (!instance) instance = new GameMgr{};
	return instance;
}

void GameMgr::update(float eTime)
{
	player->update(eTime);
}

void GameMgr::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	player->render();
}

void GameMgr::addObject(const Vector& pos, const Vector& vol, const Color& col)
{
	if (obj.size() < MAX_OBJECT)
	{
		obj.emplace_back(make_unique<GameObj>());
		obj.back()->setPos(pos);
		obj.back()->setVol(vol);
		obj.back()->setVel({ 0.5, 0, 0 });
		obj.back()->setCol(col);
	}
	else 
		cout << "Object is full. \n";
}

void GameMgr::deleteObject()
{
	for (auto& i = obj.cbegin(); i != obj.cend();)
	{
		if (i->get()->getPos().x > meter()) i = obj.erase(i);
		else ++i;
	}
}

GameController* GameMgr::getGameController() const
{
	return gameController;
}

int GameMgr::getElapsedTime()
{
	currTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currTime - prevTime;
	prevTime = currTime;
	//cout << "elapsed time (ms): " << elapsedTime << endl;

	return elapsedTime;
}
