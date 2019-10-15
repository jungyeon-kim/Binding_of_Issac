#include "stdafx.h"
#include "GameMgr.h"
#include "Renderer.h"
#include "GameObj.h"
#include "Player.h"

using namespace std;

GameMgr* GameMgr::instance{};

GameMgr::GameMgr()
{
	renderer = make_unique<Renderer>(wndSizeX, wndSizeY);
	if (!renderer->IsInitialized()) { cout << "Renderer could not be initialized.. \n"; }

	gameCon = GameController::getInstance();
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
	renderer->render();
	player->render();
}

void GameMgr::addObject(const Vector& pos, const Vector& vol, const Color& col)
{
	if (test.size() < MAX_OBJECT)
	{
		test.emplace_back(make_unique<Player>());
		test.back()->setPos(pos);
		test.back()->setVol(vol);
		test.back()->setVel({ 0.5, 0, 0 });
		test.back()->setCol(col);
	}
	else 
		cout << "Object is full. \n";
}

void GameMgr::deleteObject()
{
	for (auto& i = test.cbegin(); i != test.cend();)
	{
		if (i->get()->getPos().x > meter()) i = test.erase(i);
		else ++i;
	}
}

GameController* GameMgr::getGameController() const
{
	return gameCon;
}

int GameMgr::getElapsedTime()
{
	currTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currTime - prevTime;
	prevTime = currTime;
	//cout << "elapsed time (ms): " << elapsedTime << endl;

	return elapsedTime;
}
