#include "stdafx.h"		
#include "ObjMgr.h"
#include "Physics.h"
#include "GameActor.h"

using namespace std;

ObjMgr* ObjMgr::instance{};

ObjMgr::ObjMgr()
{
	init();
}

ObjMgr::~ObjMgr()
{
}

ObjMgr* ObjMgr::getInstance()
{
	if (!instance) instance = new ObjMgr{};
	return instance;
}

void ObjMgr::init()
{
	physics = make_unique<Physics>();
	obj = make_unique<multimap<Obj, unique_ptr<GameObj>, greater<>>>();
}

void ObjMgr::update(float eTime)
{
	// Check & Process to collision
	for (auto i = obj->begin(); i != obj->end(); ++i)
		for (auto j = i; j != obj->end(); ++j)
			if (physics->isOverlap(i->first, j->first, *i->second, *j->second) && i != j)
			{
				const auto& actorI{ dynamic_cast<GameActor*>(i->second.get()) };
				const auto& actorJ{ dynamic_cast<GameActor*>(j->second.get()) };

				if (actorI && actorJ)
				{
					actorI->takeDamage(actorJ->getDamage());
					actorJ->takeDamage(actorI->getDamage());
				}
				physics->processCollision(*i->second, *j->second);
			}

	garbageCollect();

	for (const auto& obj : *obj) obj.second->update(eTime);
}

void ObjMgr::render()
{
	for (const auto& obj : *obj) obj.second->render();
}

void ObjMgr::deleteObject(Obj name)
{
	const auto& target{ obj->find(name) };

	if (target != obj->end()) obj->erase(target);
	else cout << "Cannot delete. " << static_cast<int>(name) << " Object is not exist. \n";
}

void ObjMgr::deleteAllObject()
{
	for (auto& i = obj->cbegin(); i != obj->cend();) 
		i = obj->erase(i);
}

void ObjMgr::deleteAllObjectByException(Obj exceptedName)
{
	for (auto& i = obj->cbegin(); i != obj->cend();)
	{
		if (i->first != exceptedName) i = obj->erase(i);
		else ++i;
	}
}

void ObjMgr::garbageCollect()
{
	for (auto& i = obj->cbegin(); i != obj->cend();)
	{
		const auto& actor{ dynamic_cast<GameActor*>(i->second.get()) };

		switch (i->first)
		{
		case Obj::BLOCK_BOX: case Obj::PORTAL_BOX:
			++i;
			break;
		case Obj::PLAYER:
			++i;
			break;
		case Obj::ENEMY:
			if (actor->isReadyToDestroy()) i = obj->erase(i);
			else ++i;
			break;
		case Obj::PLAYER_BULLET: case Obj::ENEMY_BULLET:
			if (actor->isReadyToDestroy()) i = obj->erase(i);
			else ++i;
			break;
		default:
			++i;
			break;
		}
	}
}