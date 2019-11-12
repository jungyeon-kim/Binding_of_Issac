#pragma once

template <typename T>
void GameMgr::addObject(const std::string& name, const Vector& pos)
{
	if (obj->size() < MAX_OBJECT) obj->emplace(name, make_unique<T>(pos));
	else cout << "Object is full. \n";
}

template<typename T>
void GameMgr::addObject(const std::string& name, const Vector& pos, const Vector& vel)
{
	if (obj->size() < MAX_OBJECT) obj->emplace(name, make_unique<T>(pos, vel));
	else cout << "Object is full. \n";
}

// This function must use with code for check end list.
template<typename T>
T* GameMgr::getObj(const std::string& name) const
{
	return dynamic_cast<T*>(obj->find(name)->second.get());
}
