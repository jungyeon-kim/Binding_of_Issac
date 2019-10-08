#include "stdafx.h"
#include "GameMgr.h"
#include "Renderer.h"
#include "GameObj.h"

using namespace std;

GameMgr* GameMgr::instance{};

GameMgr::GameMgr()
{
	// Initialize Renderer
	renderer = make_unique<Renderer>(wndSizeX, wndSizeY);
	if (!renderer->IsInitialized()) { cout << "Renderer could not be initialized.. \n"; }
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
	for (auto& i : obj) i->update(eTime);
}

void GameMgr::renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	// renderer Test
	for (const auto& i : obj)
	{
		Vector pos{ i->getPos() };
		Vector vol{ i->getVol() };
		Color col{ i->getCol() };

		renderer->DrawSolidRect(pos.x, pos.y, pos.z, vol.x,
			col.r, col.g, col.b, col.a);
	}
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
	for (const auto& i : obj)
	{
		obj.remove(i);
		break;
	}
}

void GameMgr::testKeyInput(unsigned char c)
{
	static float loc{};

	if (c == 'a')
	{
		addObject({ 1 * loc, 1 * loc, 0 }, { 1, 1, 1 }, { 1, 0, 0, 1 });
		if(loc < MAX_OBJECT) ++loc;
	}

	if (c == 'd')
	{
		if (!obj.empty()) --loc;
		deleteObject();
	}
}

int GameMgr::getElapsedTime()
{
	currTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currTime - prevTime;
	prevTime = currTime;
	cout << "elapsed time (ms): " << elapsedTime << endl;

	return elapsedTime;
}
