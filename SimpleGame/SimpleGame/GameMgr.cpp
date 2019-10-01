#include "stdafx.h"
#include "GameMgr.h"
#include "Renderer.h"
#include "GameObj.h"

#include <memory>

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

void GameMgr::renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	// renderer Test
	for (int i = 0; i < MAX_OBJECT; ++i)
		if (obj[i])
		{
			Vector pos{ obj[i]->getPos() };
			Vector vol{ obj[i]->getVol() };
			Color col{ obj[i]->getCol() };

			renderer->DrawSolidRect(pos.x, pos.y, pos.z, vol.x,
				col.r, col.g, col.b, col.a);
		}
}

int GameMgr::addObject(const Vector& pos, const Vector& vol, const Color& col)
{
	int idx{ -1 };

	for (int i = 0; i < MAX_OBJECT; ++i)
		if (!obj[i])
		{
			idx = i;
			break;
		}
	if (idx == -1) { cout << "Object is full. \n"; return idx; }

	obj[idx] = make_unique<GameObj>();
	obj[idx]->setPos(pos);
	obj[idx]->setVol(vol);
	obj[idx]->setCol(col);
	
	return idx;
}

void GameMgr::deleteObject(int idx)
{
	if (idx < 0) { cout << "Negative Idx is not allow. \n"; return; }
	if (idx >= MAX_OBJECT) { cout << "Idx exceeds MAX_OBJECT \n"; return; }
	if (obj[idx]) obj[idx].reset();
}

void GameMgr::testKeyInput(unsigned char c)
{
	static float loc{};

	if (c == 'a')
	{
		addObject({ 20 * loc, 20 * loc, 0 }, { 20, 20, 20}, { 1, 0, 0, 1 });
		if(loc < MAX_OBJECT) ++loc;
	}

	if (c == 'd')
	{
		for (int i = 0; i < MAX_OBJECT; ++i)
			if (obj[i])
			{
				deleteObject(i);
				--loc;
				break;
			}
	}
}
