#include "stdafx.h"
#include "Fly.h"
#include "TexMgr.h"
#include "ObjMgr.h"
#include "Physics.h"
#include "Renderer.h"
#include "Player.h"

Fly::Fly(const Vector& pos)
{
	init(pos);
}

Fly::~Fly()
{
}

void Fly::init(const Vector& pos)
{
	texID.emplace_back(texMgr->getTexture(Tex::ENEMY_FLY));
	texID.emplace_back(texMgr->getTexture(Tex::P_BLOOD4));
	currAnimX[0] = uidAnimX(dre);

	maxHP = 10.0f;
	currHP = maxHP;
	damage = 5.0f;

	forceAmount = 7.25f;
	fricCoef = 1.0f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.3f), meter(0.3f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 0.7f;
}

void Fly::update(float eTime)
{
	GameActor::update(eTime);

	if (currHP > 0.0f)
	{
		physics->update(*this, eTime);
		doAnimCycle(3, 4, 1, 0);
	}
	else
	{
		if (getEnableCollision()) setEnableCollision(false);
		doAnimCycle(5, 6, 1, 1);
	}
}

void Fly::render()
{
	GameActor::render();

	if (currHP > 0.0f)
	{
		static const Vector& texVol{ objVol.x * 1.5f, objVol.y * 1.5f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[0], 4, 1, currAnimX[0], currAnimY[0]);
	}
	else
	{
		static const Vector& texVol{ objVol.x * 3.0f, objVol.y * 3.0f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[1], 6, 1, currAnimX[1], currAnimY[1]);
	}
}

void Fly::addForce()
{
	const auto& player{ objMgr->tryGetObj<Player>(Obj::PLAYER) };

	if (player)
	{
		moveDir = physics->getUnit(player->getPos() - objPos);

		objForce.x = moveDir.x * forceAmount;
		objForce.y = moveDir.y * forceAmount;
	}
}

void Fly::takeDamage(float damage, Obj attackerType, const GameActor& attacker)
{
	if (attackerType == Obj::PLAYER) currHP = 0.0f;
	else if (attacker.getEnableCollision()) currHP -= damage;
}

bool Fly::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}
