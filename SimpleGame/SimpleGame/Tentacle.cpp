#include "stdafx.h"
#include "Tentacle.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"

Tentacle::Tentacle(const Vector& pos)
{
	init(pos);
}

Tentacle::~Tentacle()
{
}

void Tentacle::init(const Vector & pos)
{
	texID.emplace_back(texMgr->getTexture(Tex::ENEMY_TENTACLE));
	texID.emplace_back(texMgr->getTexture(Tex::ENEMY_DEATH1));

	maxHP = 50.0f;
	currHP = maxHP;
	damage = 20.0f;

	forceAmount;
	fricCoef = numeric_limits<float>::max();
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.8f), meter(0.8f), meter() };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;
}

void Tentacle::update(float eTime)
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

		doAnimCycle(10, 6, 0, 0);
	}
	else
	{
		setEnableCollision(false);
		doAnimCycle(5, 4, 4, 1);
	}
}

void Tentacle::render()
{
	if (currHP > 0)
	{
		renderer->DrawTextureRectAnim(objPos, objVol, objCol, texID[0], 6, 1, nextAnimX[0], 0);
		renderer->DrawSolidRectGauge(objPos, { 0.0f, meter(0.7f), 0.0f }, { objVol.x, meter(0.15f), 0.0f },
			{ 0.8f, 0.8f, 0.8f, 0.8f }, 100.0f);
		renderer->DrawSolidRectGauge(objPos, { 0.0f, meter(0.7f), 0.0f }, { objVol.x, meter(0.15f), 0.0f },
			{ 1.0f, 0.0f, 0.0f, 0.8f }, (currHP / maxHP) * 100.0f);
	}
	else
	{
		static const Vector& deathAnimVol{ objVol.x * 2.0f, objVol.y * 2.0f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, deathAnimVol, objCol, texID[1], 4, 4, nextAnimX[1], nextAnimY[1]);
	}

	GameActor::render();		// 셰이더가 z축 기준으로 렌더링 되게 바뀌면 맨 앞에서 호출할 예정
}

void Tentacle::addForce()
{
}

bool Tentacle::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}

