#include "stdafx.h"
#include "Tentacle.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "Fly.h"

using namespace std;

Tentacle::Tentacle(const Vector& pos)
{
	init(pos);
}

Tentacle::~Tentacle()
{
}

void Tentacle::init(const Vector& pos)
{
	texID.emplace_back(texMgr->getTexture(TEX::ENEMY_TENTACLE));
	texID.emplace_back(texMgr->getTexture(TEX::P_BLOOD2));
	currAnimX[0] = uidAnimX(dre);

	maxHP = 20.0f;
	currHP = maxHP;
	damage = 5.0f;

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
		physics->update(*this, eTime);

		doAnimCycle(10, 6, 1, 0);
		// Decide whether to spawn Fly
		if (!(++spawnFlyCycle % uidSpawnFlyCycle(dre)))
		{
			createFly();
			spawnFlyCycle = 0;
		}
	}
	else
	{
		if (getEnableCollision())
		{
			soundMgr->PlayShortSound(soundMgr->getSound(SOUND::DESTROY_ENEMY2), false, 0.8f);
			setEnableCollision(false);
		}
		doAnimCycle(5, 4, 4, 1);
	}
}

void Tentacle::render()
{
	GameActor::render();

	if (currHP > 0.0f)
	{
		static const Vector& texVol{ objVol.x * 1.8f, objVol.y * 1.8f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[0], 6, 1, currAnimX[0], 0);
	}
	else
	{
		const Vector& texPos{ objPos.x - meter(0.5f), objPos.y + meter(0.1f), objPos.z };
		static const Vector& texVol{ objVol.x * 3.0f, objVol.y * 3.0f, objVol.z };
		renderer->DrawTextureRectAnim(texPos, texVol, objCol, texID[1], 4, 4, currAnimX[1], currAnimY[1]);
	}
}

void Tentacle::addForce()
{
}

bool Tentacle::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}

void Tentacle::createFly()
{
	objMgr->addObject<Fly>(OBJ::SKY_ENEMY, objPos);
}

