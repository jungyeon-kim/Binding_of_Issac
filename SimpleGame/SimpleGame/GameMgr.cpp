#include "stdafx.h"
#include "GameMgr.h"
#include "Renderer.h"

GameMgr::GameMgr()
{
	// Initialize Renderer
	renderer = new Renderer{ 500, 500 };

	if (!renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

GameMgr::~GameMgr()
{
	if (!renderer)
	{
		delete renderer;
		renderer = nullptr;
	}
}

void GameMgr::renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);

	glutSwapBuffers();	// 더블버퍼링
}