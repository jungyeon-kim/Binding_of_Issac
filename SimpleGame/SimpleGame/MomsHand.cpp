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
	currAnimX[0] = 0;
	currAnimY[0] = 1;

	maxHP = 120.0f;
	currHP = maxHP;
	damage = 10.0f;

	forceAmount = 30.0f;
	fricCoef = 1.0f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.8f), meter(0.9f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 2.0f;
}

void MomsHand::update(float eTime)
{
	GameActor::update(eTime);

	if (currHP > 0.0f)
	{
		physics->update(*this, eTime);

		// Decide whether to attack
		if (!(++attackCycle % uidAttackCycle(dre)))
		{
			currAnimX[0] = 0;
			currAnimY[0] = 1;
			canAttack = true;
		}
		if (canAttack)
		{
			doAnimCycle(10, 5, 2, 0);
			attackCycle = 0;
		}
		if (currAnimX[0] == 4 && currAnimY[0] == 0 && canAttack) canAttack = false;
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
		const Vector& texPos{ objPos.x, objPos.y + meter(0.2f), objPos.z };
		static const Vector& texVol{ objVol.x * 2.0f, objVol.y * 2.0f, objVol.z };
		renderer->DrawTextureRectAnim(texPos, texVol, objCol, texID[0], 5, 2, currAnimX[0], currAnimY[0]);
	}
	else
	{
		static const Vector& texVol{ objVol.x * 5.0f, objVol.y * 4.0f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[1], 4, 4, currAnimX[1], currAnimY[1]);
	}
}

void MomsHand::addForce()
{
	if (currAnimY[0] == 0 && canAttack)
	{
		objForce.x += dirX * forceAmount;
		objForce.y += dirY * forceAmount;

		if (!dirY) objForce.x *= 1.5f;
		else if (!dirX) objForce.y *= 1.5f;
	}
	else
	{
		dirX = static_cast<float>(uidDir(dre));
		dirY = static_cast<float>(uidDir(dre));
	}
}

bool MomsHand::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}
