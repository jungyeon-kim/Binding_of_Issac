#pragma once

template <typename T>
void GameMgr::addObject(std::string objName)
{
	if (obj->size() < MAX_OBJECT)
	{
		if (objName == "Bullet") obj->emplace(objName, std::make_unique<Bullet>(
			obj->find("Player")->second->getPos(),
			obj->find("Player")->second->getVel()
			));
		else obj->emplace(objName, std::make_unique<T>());
	}
	else
		std::cout << "Object is full. \n";
}