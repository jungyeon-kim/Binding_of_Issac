#include "stdafx.h"
#include "Fly.h"
#include "TexMgr.h"
#include "Physics.h"
#include "Renderer.h"

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
	texID.emplace_back(texMgr->getTexture(Tex::P_BLOOD3));
	nextAnimX[0] = randNextAnimXY(dre);

	maxHP = 30.0f;
	currHP = maxHP;
	damage = 5.0f;

	forceAmount = 8.0f;
	fricCoef = 1.0f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.3f), meter(0.3f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;
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
		doAnimCycle(5, 4, 4, 1);
	}
}

void Fly::render()
{
	GameActor::render();

	if (currHP > 0.0f)
	{
		static const Vector& texVol{ objVol.x * 1.5f, objVol.y * 1.5f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[0], 4, 1, nextAnimX[0], nextAnimY[0]);
	}
	else
	{
		static const Vector& texVol{ objVol.x * 4.0f, objVol.y * 4.0f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[1], 4, 4, nextAnimX[1], nextAnimY[1]);
	}
}

void Fly::addForce()
{
}

bool Fly::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}
