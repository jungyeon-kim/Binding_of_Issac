#include "ObjMgr.h"
#pragma once


template<typename T>
void ObjMgr::addObject(Obj objName, Tex texName, const Vector& pos)
{
	if (obj->size() < MAX_OBJECT) obj->emplace(objName, make_unique<T>(texName, pos));
	else cout << "Object is full. \n";
}

template<typename T>
void ObjMgr::addObject(Obj objName, Tex texName, const Vector& pos, const Vector& vel)
{
	if (obj->size() < MAX_OBJECT) obj->emplace(objName, make_unique<T>(texName, pos, vel));
	else cout << "Object is full. \n";
}

// This function must use with null check
template<typename T>
T* ObjMgr::tryGetObj(Obj name) const
{
	if (obj->find(name) != obj->end()) return dynamic_cast<T*>(obj->find(name)->second.get());
	return nullptr;
}
