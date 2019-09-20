#include "stdafx.h"
#include "GameMgr.h"
#include "Renderer.h"
#include "GameObj.h"

GameMgr::GameMgr()
{
	// Initialize Renderer
	renderer = new Renderer{ wndSizeX, wndSizeY };
	if (!renderer->IsInitialized()) { std::cout << "Renderer could not be initialized.. \n"; }

	// test
	//for (float i = 0; i < 3; ++i)
	//	addObject({ 20 * i,20 * i,20 * i }, { 20, 20, 20 }, { 1, 0, 0, 1 });
}

GameMgr::~GameMgr()
{
	if (renderer)
	{
		delete renderer;
		renderer = nullptr;
	}
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

	glutSwapBuffers();	// double buffering
}

int GameMgr::addObject(ObjLocation loc, ObjSize size, ObjColor color)
{
	int idx{ -1 };

	for (int i = 0; i < MAX_OBJECT; ++i)
		if (!obj[i])
		{
			idx = i;
			break;
		}
	if (idx == -1) { std::cout << "Object is full. \n"; return -1; }

	obj[idx] = new GameObj{};
	obj[idx]->setLocation(loc);
	obj[idx]->setSize(size);
	obj[idx]->setColor(color);

	return idx;
}

void GameMgr::deleteObject(int idx)
{
	if (idx < 0) { std::cout << "Negative idx does not allowed. \n"; return; }
	if (idx >= MAX_OBJECT) { std::cout << "Idx exceeds MAX_OBJECT \n"; return; }
	if (obj[idx])
	{
		delete obj[idx];
		obj[idx] = nullptr;
	}
}

void GameMgr::testKeyInput(unsigned char c)
{
	if (c == 'a')
		addObject({0, 0, 0}, { 20, 20, 20 }, { 1, 0, 0, 1 });

	if (c == 'd')
	{
		for (int i = 0; i < MAX_OBJECT; ++i)
			if (obj[i])
			{
				deleteObject(i);
				break;
			}
	}
}
