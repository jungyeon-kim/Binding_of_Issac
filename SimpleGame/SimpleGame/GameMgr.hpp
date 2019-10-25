#include "stdafx.h"
#include "GameMgr.h"

template <typename T>
void GameMgr::addObject(std::string objName)
{
	if (bullet.size() < MAX_OBJECT)
	{
		bullet.emplace_back(make_unique<T>(player->getPos(), player->getVel()));
	}
	else
		cout << "Object is full. \n";
}