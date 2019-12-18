#pragma once

#include "ObjMgr.h"

// Do not use this on constructor of ObjMgr class.
template<typename T>
auto ObjMgr::addObject(OBJ name, const Vector& pos)
{
	if (obj->size() < MAX_OBJECT)
	{
		if (name == OBJ::GROUND_ENEMY || name == OBJ::SKY_ENEMY) ++numOfEnemy;
		return obj->emplace(name, make_unique<T>(pos));
	}
	cout << "addObject:: Object is full. \n";
	return obj->end();
}

// Do not use this on constructor of ObjMgr class.
template<typename T>
auto ObjMgr::addObject(OBJ name, TEX texID, const Vector& pos)
{
	if (obj->size() < MAX_OBJECT)
	{
		if (name == OBJ::GROUND_ENEMY || name == OBJ::SKY_ENEMY) ++numOfEnemy;
		return obj->emplace(name, make_unique<T>(texID, pos));
	}
	cout << "addObject:: Object is full. \n";
	return obj->end();
}

// This function must use with null check
template<typename T>
T* ObjMgr::tryGetObj(OBJ name) const
{
	if (obj->find(name) != obj->end()) return dynamic_cast<T*>(obj->find(name)->second.get());
	return nullptr;
}
