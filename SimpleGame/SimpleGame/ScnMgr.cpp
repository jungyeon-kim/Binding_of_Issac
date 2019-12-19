#include "stdafx.h"
#include "ScnMgr.h"
#include "ObjMgr.h"
#include "TexMgr.h"
#include "GameController.h"
#include "Renderer.h"
#include "ObjectSet.h"

using namespace std;

ScnMgr* ScnMgr::instance{};

ScnMgr::ScnMgr()
{
	init();
}

ScnMgr::~ScnMgr()
{
}

ScnMgr* ScnMgr::getInstance()
{
	if (!instance) instance = new ScnMgr{};
	return instance;
}

void ScnMgr::init()
{
	renderer = objMgr->getRenderer();
	scene = SCENE::TITLE;

	texID.emplace_back(texMgr->getTexture(TEX::SCENE_TITLE));
	texID.emplace_back(texMgr->getTexture(TEX::BACK_GROUND));
	texID.emplace_back(texMgr->getTexture(TEX::FRONT_FRAME));
	texID.emplace_back(texMgr->getTexture(TEX::SCENE_ENDING));

	setLevel("Levels/STAGE" + to_string(levelNameIdx) + ".txt");
}

void ScnMgr::update(float eTime)
{
	switch (scene)
	{
	case SCENE::TITLE:
		if (gameCon->isInputSpaceBar()) scene = SCENE::IN_GAME;
		break;
	case SCENE::IN_GAME:
	{
		const auto& player{ objMgr->tryGetObj<Player>(OBJ::PLAYER) };

		if (player)
		{
			if (onChangeLevel)
			{
				player->setPos({ 0.0f, meter(-3.0f), 0.0f });
				setLevel("Levels/STAGE" + to_string(++levelNameIdx) + ".txt");
				onChangeLevel = false;
			}
		}
		else
		{
			levelNameIdx = 0;
			objMgr->resetNumOfEnemy();
			setLevel("Levels/STAGE0.txt");
		}
		objMgr->update(eTime);
		break;
	}
	case SCENE::ENDING:
		if (!(++sceneCnt % 800))
		{
			scene = SCENE::TITLE;
			sceneCnt = 0;
		}
		break;
	}
}

void ScnMgr::render()
{
	switch (scene)
	{
	case SCENE::TITLE:
		renderer->DrawGround({ 0.0f, 0.0f, 0.0f }, { wndSizeX, wndSizeY, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texID[0], 0.0f);
		break;
	case SCENE::IN_GAME:
		renderer->DrawGround({ 0.0f, 0.0f, 0.0f }, { wndSizeX, wndSizeY, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texID[2], 0.0f);
		renderer->DrawGround({ 0.0f, 0.0f, 0.0f }, { wndSizeX, wndSizeY, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texID[1]);
		objMgr->render();
		break;
	case SCENE::ENDING:
		//renderer->DrawGround({ 0.0f, 0.0f, 0.0f }, { wndSizeX, wndSizeY, 0.0f }, { 1.0f, 1.0f, 1.0f, sceneCnt / 500.0f }, texID[3], 0.0f);
		renderer->DrawTextureRect({ 0.0f, 0.0f, 0.0f }, { wndSizeX, wndSizeY, 0.0f }, { 1.0f, 1.0f, 1.0f, sceneCnt / 500.0f }, texID[3], 0.0f);
		break;
	}
}

bool ScnMgr::readTileData(const string& fileName)
{
	tileData.open(fileName);

	if (tileData)
	{
		for (int i = 0; i < column; ++i)
			for (int j = 0; j < row; ++j)
				tileData >> levelTile[i][j];
		tileData.close();

		reverse(levelTile, levelTile + column);
		return true;
	}
	else
	{
		objMgr->deleteAllObject();
		scene = SCENE::ENDING;
		return false;
	}
}

void ScnMgr::tryChangeLevel()
{
	if (!objMgr->getNumOfEnemy()) onChangeLevel = true;
}

void ScnMgr::setLevel(const string& fileName)
{
	if (readTileData(fileName))
	{
		objMgr->deleteAllObjectByException(OBJ::PLAYER);

		for (int i = 0; i < column; ++i)
			for (int j = 0; j < row; ++j)
			{
				const Vector& tilePos{ 
					meter(static_cast<float>(j - row / 2)), 
					meter(static_cast<float>(i - (column / 2))), 
					0.0f };

				switch (hashCode(levelTile[i][j].c_str()))
				{
				case hashCode("B1"):
					objMgr->addObject<BlockBox>(OBJ::BLOCK_BOX, tilePos);
					break;
				case hashCode("B2"):
					objMgr->addObject<ObjBox>(OBJ::OBJ_BOX, TEX::OBJBOX_ROCK, tilePos);
					break;
				case hashCode("B3"):
					objMgr->addObject<PortalBox>(OBJ::PORTAL_BOX, TEX::PORTALBOX_DOOR, tilePos);
					break;
				case hashCode("P1"):
					objMgr->addObject<Player>(OBJ::PLAYER, tilePos);
					break;
				case hashCode("GE1"):
					objMgr->addObject<Tentacle>(OBJ::GROUND_ENEMY, tilePos);
					break;
				case hashCode("GE2"):
					objMgr->addObject<MomsHand>(OBJ::GROUND_ENEMY, tilePos);
					break;
				case hashCode("GE3"):
					objMgr->addObject<Polyc>(OBJ::GROUND_ENEMY, tilePos);
					break;
				case hashCode("GE4"):
					objMgr->addObject<Judas>(OBJ::GROUND_ENEMY, tilePos);
					break;
				case hashCode("SE1"):
					objMgr->addObject<Fly>(OBJ::SKY_ENEMY, tilePos);
					break;
				}
			}
	}
}

void ScnMgr::keyDownInput(unsigned char key, int x, int y) const
{
	gameCon->keyDownInput(key, x, y);
}

void ScnMgr::keyUpInput(unsigned char key, int x, int y) const
{
	gameCon->keyUpInput(key, x, y);
}

void ScnMgr::specialKeyDownInput(int key, int x, int y) const
{
	gameCon->specialKeyDownInput(key, x, y);
}

void ScnMgr::specialKeyUpInput(int key, int x, int y) const
{
	gameCon->specialKeyUpInput(key, x, y);
}

int ScnMgr::getElapsedTime()
{
	currTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currTime - prevTime;
	prevTime = currTime;
	//cout << "elapsed time (ms): " << elapsedTime << endl;

	return elapsedTime;
}