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
			ObjLocation loc{ obj[i]->getLocation() };
			ObjSize size{ obj[i]->getSize() };
			ObjColor color{ obj[i]->getColor() };

			renderer->DrawSolidRect(loc.posX, loc.posY, loc.posZ, size.sizeX,
				color.colorR, color.colorG, color.colorB, color.colorA);
		}
}

int GameMgr::addObject(const ObjLocation& loc, const ObjSize& size, const ObjColor& color)
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
	obj[idx]->setLocation(loc);
	obj[idx]->setSize(size);
	obj[idx]->setColor(color);
	
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
		addObject({ 20 * loc, 20 * loc, 0 }, { 20, 20, 20 }, { 1, 0, 0, 1 });
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
