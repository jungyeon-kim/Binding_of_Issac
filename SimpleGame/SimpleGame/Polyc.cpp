#include "stdafx.h"
#include "Polyc.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"
#include "ObjMgr.h"

using namespace std;

Polyc::Polyc(const Vector& pos)
{
	init(pos);
}

Polyc::~Polyc()
{
}

void Polyc::init(const Vector& pos)
{
	texID.emplace_back(texMgr->getTexture(Tex::ENEMY_POLYC));
	texID.emplace_back(texMgr->getTexture(Tex::P_BLOOD2));
	nextAnimX[0] = randNextAnimXY(dre);
	nextAnimY[0] = randNextAnimXY(dre);

	maxHP = 50.0f;
	currHP = maxHP;
	damage = 20.0f;

	forceAmount;
	fricCoef = numeric_limits<float>::max();
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.9f), meter(0.9f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;
}

void Polyc::update(float eTime)
{
	GameActor::update(eTime);

	if (currHP > 0.0f)
	{
		physics->update(*this, eTime);
		doAnimCycle(15, 4, 1, 0);
	}
	else
	{
		if (getEnableCollision()) setEnableCollision(false);
		doAnimCycle(5, 4, 4, 1);
	}
}

void Polyc::render()
{
	GameActor::render();

	if (currHP > 0)
	{
		static const Vector& texVol{ objVol.x * 1.8f, objVol.y * 1.8f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[0], 4, 1, nextAnimX[0], 0);
	}
	else
	{
		const Vector& texPos{ objPos.x - meter(1.2f), objPos.y + meter(0.5f), objPos.z };
		static const Vector& texVol{ objVol.x * 3.0f, objVol.y * 3.0f, objVol.z };
		renderer->DrawTextureRectAnim(texPos, texVol, objCol, texID[1], 4, 4, nextAnimX[1], nextAnimY[1]);
	}
}

void Polyc::addForce()
{
}

bool Polyc::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}
