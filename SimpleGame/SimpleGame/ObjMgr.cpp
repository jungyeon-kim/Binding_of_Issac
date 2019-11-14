#include "stdafx.h"		
#include "ObjMgr.h"
#include "Physics.h"
#include "GameController.h"
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
	physics = make_unique<Physics>();
	gameCon = GameController::getInstance();
	obj = make_unique<multimap<Obj, unique_ptr<GameObj>, greater<>>>();

	addObject<Player>(Obj::PLAYER, { 0.0f, 0.0f, 0.0f });
}

void ObjMgr::update(float eTime)
{
	const auto& player{ tryGetObj<Player>(Obj::PLAYER) };

	if (player)
		// Decide whether to fire a Bullet
		if (gameCon->isShoot() && player->isEndCoolTime(Skill::SHOOT))
		{
			addObject<Bullet>(Obj::BULLET, player->getPos(), player->getVel());
			player->resetCoolTime(Skill::SHOOT);
		}

	garbageCollect();

	for (const auto& obj : *obj) obj.second->update(eTime);
}

void ObjMgr::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.5f, 0.5f, 1.0f);

	for (const auto& obj : *obj) obj.second->render();
}

void ObjMgr::deleteObject(Obj name)
{
	const auto& target{ obj->find(name) };

	if (target != obj->end()) obj->erase(target);
	else cout << "Cannot delete. " << static_cast<int>(name) << " Object is not exist. \n";
}

void ObjMgr::garbageCollect()
{
	for (auto& i = obj->cbegin(); i != obj->cend();)
		switch (i->first)
		{
		case Obj::PLAYER:
			++i;
			break;
		case Obj::BULLET:
			if (!physics->calcScalar(i->second->getVel())) i = obj->erase(i);
			else ++i;
			break;
		}
}