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

	// Add Hero Object Test
	obj.emplace_back(make_unique<GameObj>());
	obj[HERO_OBJECT]->setPos({ 0,0,0 });
	obj[HERO_OBJECT]->setVol({ 1, 1, 1 });
	obj[HERO_OBJECT]->setVel({ 0, 0, 0 });
	obj[HERO_OBJECT]->setCol({ 1, 0, 0, 0 });
	obj[HERO_OBJECT]->setWt(1);
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
	float fAmount{ 1 };
	float fX{}, fY{}, fZ{};

	if (keyW) fY += fAmount;
	if (keyA) fX -= fAmount;
	if (keyS) fY -= fAmount;
	if (keyD) fX += fAmount;

	obj[HERO_OBJECT]->addForce(fX, fY, fZ, eTime);

	for (const auto& i : obj) i->update(eTime);
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
	for (auto& i = obj.cbegin(); i != obj.cend();)
	{
		if (i->get()->getPos().x > meter()) i = obj.erase(i);
		else ++i;
	}
}

void GameMgr::keyDownInput(unsigned char key, int x, int y)
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

void GameMgr::keyUpInput(unsigned char key, int x, int y)
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

void GameMgr::testKeyInput(unsigned char c)
{
	if (c == 'a') addObject({ 0, 0, 0 }, { 1, 1, 1 }, { 1, 0, 0, 1 });
	if (c == 'd') deleteObject();
}

int GameMgr::getElapsedTime()
{
	currTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currTime - prevTime;
	prevTime = currTime;
	//cout << "elapsed time (ms): " << elapsedTime << endl;

	return elapsedTime;
}
