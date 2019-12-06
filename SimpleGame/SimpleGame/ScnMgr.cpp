#include "stdafx.h"
#include "ScnMgr.h"
#include "ObjMgr.h"
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
	objMgr = ObjMgr::getInstance();

	// test
	constexpr int column{ wndSizeX / 100 };
	constexpr int row{ wndSizeY / 100 };
	int arr[row][column]
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	for(int i = 0; i < column; ++i)
		for (int j = 0; j < row; ++j)
			switch (arr[j][i])
			{
			case 1:
				objMgr->addObject<BlockBox>(Obj::BLOCK_BOX, { meter(i - column / 2), meter(j - row / 2), 0.0f });
				break;
			case 2:
				objMgr->addObject<Enemy>(Obj::ENEMY, { meter(i - column / 2), meter(j - row / 2), 0.0f });
				break;
			}
	//

	objMgr->addObject<Player>(Obj::PLAYER, { 0.0f, 0.0f, 0.0f });
	// test
	//objMgr->addObject<Enemy>(Obj::ENEMY, { meter(2), 0.0f, 0.0f });
	//objMgr->addObject<Enemy>(Obj::ENEMY, { meter(2), meter(3), 0.0f });
	//objMgr->addObject<Enemy>(Obj::ENEMY, { meter(-5), meter(), 0.0f });
	//
}