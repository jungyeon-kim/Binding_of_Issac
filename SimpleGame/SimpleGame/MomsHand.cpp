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
	texID.emplace_back(texMgr->getTexture(Tex::ENEMY_DEATH));

	maxHP = 100.0f;
	currHP = maxHP;
	damage = 10.0f;

	forceAmount = 25.0f;
	fricCoef = 1.0f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(2.0f), meter(2.0f), meter(2.0f) };
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

		// update Physics
		objAcc = physics->getAcc(objAcc, objForce, objMass);
		objVel = physics->getVel(objVel, objAcc, eTime);
		objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
		objPos = physics->getPos(objPos, objVel, objAcc, eTime);

		doAnimCycle(10, 5, 2);
	}
	else
	{
		setEnableCollision(false);
		doAnimCycle(5, 4, 4);
	}
}

void MomsHand::render()
{
	if (currHP > 0.0f)
	{
		renderer->DrawTextureRectAnim(objPos, objVol, objCol, texID[0], 5, 2, nextAnimX, nextAnimY);
		renderer->DrawSolidRectGauge(objPos, { 0.0f, meter(0.7f), 0.0f }, { objVol.x, meter(0.15f), 0.0f },
			{ 0.8f, 0.8f, 0.8f, 0.8f }, 100.0f);
		renderer->DrawSolidRectGauge(objPos, { 0.0f, meter(0.7f), 0.0f }, { objVol.x, meter(0.15f), 0.0f },
			{ 1.0f, 0.0f, 0.0f, 0.8f }, (currHP / maxHP) * 100.0f);
	}
	else
	{
		static const Vector& deathAnimVol{ objVol.x * 2.0f, objVol.y * 2.0f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, deathAnimVol, objCol, texID[1], 4, 4, nextAnimX, nextAnimY);
	}

	GameActor::render();		// 셰이더가 z축 기준으로 렌더링 되게 바뀌면 맨 앞에서 호출할 예정
}

void MomsHand::addForce()
{
	if (nextAnimY == 0)
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
	return currHP <= 0.0f && nextAnimX == 3 && nextAnimY == 3;
}
