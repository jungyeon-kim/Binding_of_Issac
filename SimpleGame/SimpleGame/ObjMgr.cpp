#include "stdafx.h"		
#include "ObjMgr.h"
#include "Physics.h"
#include "Renderer.h"
#include "Sound.h"
#include "ObjectSet.h"

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
	physics = make_shared<Physics>();
	renderer = make_shared<Renderer>(wndSizeX, wndSizeY);
	sound = make_shared<Sound>();
	obj = make_unique<multimap<OBJ, unique_ptr<GameObj>, greater<>>>();
}


void ObjMgr::update(float eTime)
{
	// Check & Process to collision
	for (auto i = obj->begin(); i != obj->end(); ++i)
		for (auto j = i; j != obj->end(); ++j)
			if (physics->isOverlap(i->first, j->first, *i->second, *j->second) && i != j)
			{
				// About All Objects
				physics->processCollision(*i->second, *j->second);

				// About All Actors
				const auto& actorI{ dynamic_cast<GameActor*>(i->second.get()) };
				const auto& actorJ{ dynamic_cast<GameActor*>(j->second.get()) };

				if (actorI && actorJ)
				{
					actorI->takeDamage(actorJ->getDamage(), j->first, *actorJ);
					actorJ->takeDamage(actorI->getDamage(), i->first, *actorI);
				}

				// About PortalBox & Player
				const auto& player{ dynamic_cast<Player*>(i->second.get()) };
				const auto& portal{ dynamic_cast<PortalBox*>(j->second.get()) };

				if (portal && player)
				{
					portal->tryOpenDoor();
				}

				// About Bullet
				if (i->first == OBJ::ENEMY_BULLET || i->first == OBJ::PLAYER_BULLET)
				{
					const auto& bullet{ dynamic_cast<Bullet*>(i->second.get()) };
					if (bullet && j->second->getEnableCollision()) bullet->setCurrHP(0.0f);
				}
			}

	garbageCollect();

	for (const auto& obj : *obj) obj.second->update(eTime);
}

void ObjMgr::render()
{
	for (const auto& obj : *obj) obj.second->render();
}

void ObjMgr::deleteObject(OBJ name)
{
	const auto& target{ obj->find(name) };

	if (target != obj->end()) obj->erase(target);
	else cout << "deleteObject:: Cannot delete. " << static_cast<int>(name) << " Object is not exist. \n";
}

void ObjMgr::deleteAllObject()
{
	for (auto& i = obj->cbegin(); i != obj->cend();) 
		i = obj->erase(i);
}

void ObjMgr::deleteAllObjectByException(OBJ exceptedName)
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
		switch (i->first)
		{
		case OBJ::BLOCK_BOX: case OBJ::PORTAL_BOX: case OBJ::OBJ_BOX:
			if (i->second->isReadyToDestroy()) i = obj->erase(i);
			else ++i;
			break;
		case OBJ::PLAYER:
			if (i->second->isReadyToDestroy()) i = obj->erase(i);
			else ++i;
			break;
		case OBJ::GROUND_ENEMY: case OBJ::SKY_ENEMY:
			if (i->second->isReadyToDestroy())
			{
				i = obj->erase(i);
				--numOfEnemy;
			}
			else ++i;
			break;
		case OBJ::PLAYER_BULLET: case OBJ::ENEMY_BULLET:
			if (i->second->isReadyToDestroy()) i = obj->erase(i);
			else ++i;
			break;
		default:
			++i;
			break;
		}
	}
}

int ObjMgr::getNumOfEnemy() const
{
	return  numOfEnemy;
}

void ObjMgr::resetNumOfEnemy()
{
	numOfEnemy = 0;
}

shared_ptr<Physics> ObjMgr::getPhysics() const
{
	return physics;
}

shared_ptr<Renderer> ObjMgr::getRenderer() const
{
	return renderer;
}

shared_ptr<Sound> ObjMgr::getSound() const
{
	return sound;
}
