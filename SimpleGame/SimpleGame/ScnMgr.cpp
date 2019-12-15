#include "stdafx.h"
#include "ScnMgr.h"
#include "ObjMgr.h"
#include "TexMgr.h"
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
	texID.emplace_back(texMgr->getTexture(Tex::BACK_GROUND));
	texID.emplace_back(texMgr->getTexture(Tex::FRONT_FRAME));

	setLevel("Levels/STAGE" + to_string(levelNameIdx) + ".txt");
}

void ScnMgr::update(float eTime)
{
	if (canChangeLevel)
	{
		const auto& player{ objMgr->tryGetObj<Player>(Obj::PLAYER) };

		if (player) player->setPos({ 0.0f, meter(-3.0f), 0.0f });
		setLevel("Levels/STAGE" + to_string(++levelNameIdx) + ".txt");
		canChangeLevel = false;
	}
}

void ScnMgr::render()
{
	renderer->DrawGround({ 0.0f, 0.0f, 0.0f }, { wndSizeX, wndSizeY, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texID[1], 0.0f);
	renderer->DrawGround({ 0.0f, 0.0f, 0.0f }, { wndSizeX, wndSizeY, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texID[0]);
}

bool ScnMgr::readTileData(string fileName)
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
		cout << "readTileData:: File loading is failed. \n";
		return false;
	}
}

void ScnMgr::tryChangeLevel()
{
	if (!objMgr->getNumOfEnemy()) canChangeLevel = true;
}

void ScnMgr::setLevel(string fileName)
{
	if (readTileData(fileName))
	{
		objMgr->deleteAllObjectByException(Obj::PLAYER);

		for (int i = 0; i < column; ++i)
			for (int j = 0; j < row; ++j)
			{
				if (levelTile[i][j] > 3) objMgr->setNumOfEnemy(objMgr->getNumOfEnemy() + 1);

				const Vector& tilePos{ 
					meter(static_cast<float>(j - row / 2)), 
					meter(static_cast<float>(i - (column / 2))), 
					0.0f };

				switch (levelTile[i][j])
				{
				case -1:
					objMgr->addObject<ObjBox>(Obj::OBJ_BOX, Tex::OBJBOX_ROCK, tilePos);
					break;
				case 1:
					objMgr->addObject<BlockBox>(Obj::BLOCK_BOX, tilePos);
					break;
				case 2:
					objMgr->addObject<PortalBox>(Obj::PORTAL_BOX, Tex::PORTALBOX_DOOR, tilePos);
					break;
				case 3:
					objMgr->addObject<Player>(Obj::PLAYER, tilePos);
					break;
				case 4:
					objMgr->addObject<MomsHand>(Obj::GROUND_ENEMY, tilePos);
					break;
				case 5:
					objMgr->addObject<Tentacle>(Obj::GROUND_ENEMY, tilePos);
					break;
				case 6:
					objMgr->addObject<Polyc>(Obj::GROUND_ENEMY, tilePos);
					break;
				case 7:
					objMgr->addObject<Fly>(Obj::SKY_ENEMY, tilePos);
					break;
				}
			}
	}
}