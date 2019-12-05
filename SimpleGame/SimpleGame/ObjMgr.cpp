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
	// test
	addObject<Enemy>(Obj::ENEMY, { meter(2), 0.0f, 0.0f });
	addObject<Enemy>(Obj::ENEMY, { meter(2), meter(3), 0.0f });
	addObject<Enemy>(Obj::ENEMY, { meter(-5), meter(), 0.0f });
	addObject<BlockBox>(Obj::BLOCK_BOX, { meter(-6), meter(-2), 0.0f });
	//
}

void ObjMgr::update(float eTime)
{
	const auto& player{ tryGetObj<Player>(Obj::PLAYER) };

	if (player)
		// Decide whether to spawn a Bullet of Player
		if (gameCon->isShoot() && player->isEndCoolTime(Skill::SHOOT))
		{
			addObject<Bullet>(Obj::BULLET, player->getPos(), player->getVel());
			player->resetCoolTime(Skill::SHOOT);
		}

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
	{
		const auto& actor{ dynamic_cast<GameActor*>(i->second.get()) };

		switch (i->first)
		{
		case Obj::PLAYER:
			++i;
			break;
		case Obj::ENEMY:
			if (actor->getCurrHP() <= 0) i = obj->erase(i);
			else ++i;
			break;
		case Obj::BULLET:
			if (!physics->getScalar(i->second->getVel())) i = obj->erase(i);
			else if (actor->getCurrHP() <= 0) i = obj->erase(i);
			else ++i;
			break;
		default:
			++i;
			break;
		}
	}
}