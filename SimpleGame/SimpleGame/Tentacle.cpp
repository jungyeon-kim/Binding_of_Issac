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
	texID.emplace_back(texMgr->getTexture(Tex::P_BLOOD2));

	maxHP = 20.0f;
	currHP = maxHP;
	damage = 20.0f;

	forceAmount;
	fricCoef = numeric_limits<float>::max();
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.4f), meter(0.4f), 0.0f };
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

		// Update Physics
		objAcc = physics->getAcc(objAcc, objForce, objMass);
		objVel = physics->getVel(objVel, objAcc, eTime);
		objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
		objPos = physics->getPos(objPos, objVel, objAcc, eTime);

		doAnimCycle(10, 6, 0, 0);
	}
	else
	{
		if (getEnableCollision()) setEnableCollision(false);
		doAnimCycle(5, 4, 4, 1);
	}
}

void Tentacle::render()
{
	GameActor::render();

	if (currHP > 0)
	{
		static const Vector& texVol{ objVol.x * 1.8f, objVol.y * 1.8f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[0], 6, 1, nextAnimX[0], 0);
	}
	else
	{
		const Vector& texPos{ objPos.x - meter(0.5f), objPos.y + meter(0.25f), objPos.z };
		static const Vector& texVol{ objVol.x * 3.0f, objVol.y * 3.0f, objVol.z };
		renderer->DrawTextureRectAnim(texPos, texVol, objCol, texID[1], 4, 4, nextAnimX[1], nextAnimY[1]);
	}
}

void Tentacle::addForce()
{
}

bool Tentacle::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}

