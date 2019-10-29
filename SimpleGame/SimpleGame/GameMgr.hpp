#pragma once

template <typename T>
void GameMgr::addObject(const std::string& name, const Vector& pos)
{
	if (obj->size() < MAX_OBJECT)
	{
		if (name == "Bullet")
			obj->emplace(name, make_unique<Bullet>(pos, obj->find("Player")->second->getVel()));
		else obj->emplace(name, make_unique<T>(pos));
	}
	else
		std::cout << "Object is full. \n";
}