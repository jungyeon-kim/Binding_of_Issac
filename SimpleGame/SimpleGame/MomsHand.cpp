#include "stdafx.h"
#include "MomsHand.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"

MomsHand::MomsHand(const Vector& pos)
{
	init(pos);
}

MomsHand::~MomsHand()
{
}

void MomsHand::init(const Vector& pos)
{
	texID.emplace_back(texMgr->getTexture(Tex::ENEMY_MOMS_HAND));
	texID.emplace_back(texMgr->getTexture(Tex::P_BLOOD1));

	maxHP = 100.0f;
	currHP = maxHP;
	damage = 10.0f;

	forceAmount = 25.0f;
	fricCoef = 1.0f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(), meter(), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 2.0f;
}

void MomsHand::update(float eTime)
{
	GameActor::update(eTime);

	if (currHP > 0.0f)
	{
		objForce = { 0.0f, 0.0f, 0.0f };
		addForce();

		// Update Physics
		objAcc = physics->getAcc(objAcc, objForce, objMass);
		objVel = physics->getVel(objVel, objAcc, eTime);
		objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
		objPos = physics->getPos(objPos, objVel, objAcc, eTime);

		doAnimCycle(10, 5, 2, 0);
	}
	else
	{
		if (getEnableCollision()) setEnableCollision(false);
		doAnimCycle(5, 4, 4, 1);
	}
}

void MomsHand::render()
{
	GameActor::render();

	if (currHP > 0.0f)
	{
		const Vector& texPos{ objPos.x, objPos.y + meter(0.3f), objPos.z };
		static const Vector& texVol{ objVol.x * 2.0f, objVol.y * 2.0f, objVol.z };
		renderer->DrawTextureRectAnim(texPos, texVol, objCol, texID[0], 5, 2, nextAnimX[0], nextAnimY[0]);
	}
	else
	{
		static const Vector& texVol{ objVol.x * 4.0f, objVol.y * 4.0f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[1], 4, 4, nextAnimX[1], nextAnimY[1]);
	}
}

void MomsHand::addForce()
{
	if (nextAnimY[0] == 0)
	{
		objForce.x += dirX * forceAmount;
		objForce.y += dirY * forceAmount;
	}
	else
	{
		dirX = static_cast<float>(uidX(dre));
		dirY = static_cast<float>(uidY(dre));
	}
}

bool MomsHand::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}
