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
	renderer = make_unique<Renderer>(wndSizeX, wndSizeY);

	texID.emplace_back(texMgr->getTexture(Tex::BACK_GROUND));
	texID.emplace_back(texMgr->getTexture(Tex::FRONT_FRAME));

	setLevel("Levels/STAGE" + to_string(levelNameIdx) + ".txt");
	objMgr->addObject<Player>(Obj::PLAYER, { 0, 0, 0 });
}

void ScnMgr::update(float eTime)
{
	if (readyToGoNextLevel)
	{
		const auto& player{ objMgr->tryGetObj<Player>(Obj::PLAYER) };

		if (player) player->setPos({ 0.0f, meter(-3.0f), 0.0f });
		setLevel("Levels/STAGE" + to_string(++levelNameIdx) + ".txt");
		readyToGoNextLevel = false;
	}
}

void ScnMgr::render()
{
	// background test
	//renderer->DrawTextureRect({ 0.0f, 0.0f, 0.0f }, { wndSizeX, wndSizeY, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texID[0]);
	//renderer->DrawTextureRect({ 0.0f, 0.0f, 0.0f }, { wndSizeX, wndSizeY, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texID[1]);
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

void ScnMgr::setLevel(string fileName)
{
	if (readTileData(fileName))
	{
		objMgr->deleteAllObjectByException(Obj::PLAYER);

		for (int i = 0; i < column; ++i)
			for (int j = 0; j < row; ++j)
			{
				const Vector& tilePos{ 
					meter(static_cast<float>(j - row / 2)), 
					meter(static_cast<float>(i - column / 2)), 
					0.0f };

				switch (levelTile[i][j])
				{
				case -1:
					objMgr->addObject<BlockBox>(Obj::BLOCK_BOX, tilePos, Tex::BLOCKBOX_ROCK);
					break;
				case 1:
					objMgr->addObject<BlockBox>(Obj::BLOCK_BOX, tilePos);
					break;
				case 2:
					objMgr->addObject<PortalBox>(Obj::PORTAL_BOX, tilePos, Tex::PORTALBOX_DOOR);
					break;
				case 3:
					objMgr->addObject<Player>(Obj::PLAYER, tilePos);
					break;
				case 4:
					objMgr->addObject<MomsHand>(Obj::ENEMY, tilePos);
					break;
				case 5:
					objMgr->addObject<Tentacle>(Obj::ENEMY, tilePos);
					break;
				}
			}
	}
}

bool ScnMgr::getReadyToGoNextLevel() const
{
	return readyToGoNextLevel;
}

void ScnMgr::setReadyToGoNextLevel(bool boolean)
{
	readyToGoNextLevel = boolean;
}
