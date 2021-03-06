#include "stdafx.h"
#include "Polyc.h"
#include "objMgr.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"
#include "SoundMgr.h"
#include "Bullet.h"

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
	texID.emplace_back(texMgr->getTexture(TEX::ENEMY_POLYC));
	texID.emplace_back(texMgr->getTexture(TEX::P_BLOOD5));
	currAnimX[0] = 3;

	maxHP = 120.0f;
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

		// Decide whether to attack
		if (!(++attackCycle % uidAttackCycle(dre)))
		{
			canAttack = true;
			doOnceFlag = true;
		}
		if (canAttack) doAnimCycle(10, 4, 1, 0);
		if (currAnimX[0] == 2 && canAttack)
		{
			soundMgr->PlayShortSound(soundMgr->getSound(SOUND::YELL_ENEMY4), false, 0.6f);
			createBullet(0.0f, 360.0f, 30.0f, 0.15f, 5.0f, 15.0f);
			attackCycle = 0;
			canAttack = false;
		}
		else if (doOnceFlag)
		{	// Can't get sprite and use it temporarily
			if (attackCycle == 30) currAnimX[0] = 1;
			else if (attackCycle == 40) currAnimX[0] = 0;
			else if (attackCycle == 50) currAnimX[0] = 3;
		}
	}
	else
	{
		if (getEnableCollision())
		{
			soundMgr->PlayShortSound(soundMgr->getSound(SOUND::DESTROY_ENEMY3), false, 0.6f);
			setEnableCollision(false);
		}
		doAnimCycle(8, 4, 2, 1);
	}
}

void Polyc::render()
{
	GameActor::render();

	if (currHP > 0.0f)
	{
		static const Vector& texVol{ objVol.x * 1.8f, objVol.y * 1.8f, objVol.z };
		renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[0], 4, 1, currAnimX[0], 0);
	}
	else
	{
		const Vector& texPos{ objPos.x, objPos.y + meter(0.7f), objPos.z };
		static const Vector& texVol{ objVol.x * 3.0f, objVol.y * 3.0f, objVol.z };
		renderer->DrawTextureRectAnim(texPos, texVol, objCol, texID[1], 4, 2, currAnimX[1], currAnimY[1]);
	}
}

void Polyc::addForce()
{
}

bool Polyc::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}

void Polyc::createBullet(float first, float last, float plus, float fricCoef, float forceAmount, float damage)
{
	for (float i = first; i < last; i += plus)
	{
		const auto& obj{ objMgr->addObject<Bullet>(OBJ::ENEMY_BULLET, TEX::ENEMY_BULLET, objPos) };
		const auto& bullet{ dynamic_cast<Bullet*>(obj->second.get()) };

		bullet->setFricCoef(fricCoef);
		bullet->setForceAmount(forceAmount);
		bullet->setDamage(damage);
		bullet->setForce({ bullet->getForceAmount() * cos(angle(i)),
			bullet->getForceAmount() * sin(angle(i)), 0.0f });
		bullet->setVel(bullet->getForce());
	}
}
