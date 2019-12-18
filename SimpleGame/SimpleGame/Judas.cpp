#include "stdafx.h"
#include "Judas.h"
#include "TexMgr.h"
#include "ObjMgr.h"
#include "Physics.h"
#include "Renderer.h"
#include "Bullet.h"

using namespace std;

Judas::Judas(const Vector& pos)
{
	init(pos);
}

Judas::~Judas()
{
}

void Judas::init(const Vector& pos)
{
	texID.emplace_back(texMgr->getTexture(Tex::ENEMY_JUDAS));
	texID.emplace_back(texMgr->getTexture(Tex::P_BLOOD5));

	maxHP = 600.0f;
	currHP = maxHP;
	damage = 20.0f;

	forceAmount;
	fricCoef = numeric_limits<float>::max();
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.6f), meter(0.6f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;
}

void Judas::update(float eTime)
{
	GameActor::update(eTime);

	if (currHP > 0.0f)
	{
		physics->update(*this, eTime);

		// Decide phase state
		currHPRatio = currHP / maxHP * 100.0f;
		if (60.0f < currHPRatio && currHPRatio <= 95.0f) phase = 1;
		else if (30.0f < currHPRatio && currHPRatio <= 60.0f) phase = 2;
		else if (0.0f < currHPRatio && currHPRatio <= 30.0f) phase = 3;
		
		// Decide whether to attack type
		static float value;
		for (auto& i : attackCycle) ++i;
		switch (phase)
		{
		case 1:
			if (attackCycle[0] % 300 == 150) createBullet(10.0f, 370.0f, 20.0f, 0.005f, 1.0f, 10.0f);
			else if (!(attackCycle[0] % 300))
			{
				createBullet(0.0f, 360.0f, 20.0f, 0.005f, 1.0f, 10.0f);
				attackCycle[0] = 0;
			}
			if (!(attackCycle[1] % uidAttackCycle(dre)))
			{
				createBullet(0.0f, 360.0f, 45.0f, 0.005f, 2.5f, 15.0f,
					{ 0.0f, 1.0f, 0.0f, 1.0f }, { meter(0.4f), meter(0.4f), 0.0f });
				attackCycle[1] = 0;
			}
			break;
		case 2:
			if (!(attackCycle[0] % 10))
			{
				value = fmod(value += 20.0f, 360.0f);
				for (float i = 0; i != 360.0f; i += 90.0f)
					createBullet(value + i, 0.005f, 3.0f, 10.0f);
				attackCycle[0] = 0;
			}
			break;
		case 3:
			if (!(attackCycle[0] % 5))
			{
				value = fmod(value += 20.0f, 360.0f);
				for (float i = 0; i != 360.0f; i += 60.0f)
					createBullet(value + i, 0.005f, 5.0f, 1.0f, { 0.0f, 0.0f, 0.0f, 0.3f });
				attackCycle[0] = 0;
			}
			break;
		}
	}
	else
	{
		if (getEnableCollision()) setEnableCollision(false);
		doAnimCycle(8, 4, 2, 1);
	}
}

void Judas::render()
{
	GameActor::render();

	if (currHP > 0.0f)
	{
		static const Vector& texVol{ objVol.x * 1.5f, objVol.y * 1.1f, objVol.z };
		renderer->DrawTextureRect(objPos, texVol, objCol, texID[0]);
	}
	else
	{
		const Vector& texPos{ objPos.x, objPos.y + meter(0.7f), objPos.z };
		static const Vector& texVol{ objVol.x * 3.0f, objVol.y * 3.0f, objVol.z };
		renderer->DrawTextureRectAnim(texPos, texVol, objCol, texID[1], 4, 2, currAnimX[1], currAnimY[1]);
	}
}

void Judas::addForce()
{
}

bool Judas::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}

void Judas::createBullet(float first, float last, float plus, 
	float fricCoef, float forceAmount, float damage, const Color& col, const Vector& vol)
{
	for (float i = first; i < last; i += plus)
	{
		const auto& obj{ objMgr->addObject<Bullet>(Obj::ENEMY_BULLET, Tex::ENEMY_BULLET, objPos) };
		const auto& bullet{ dynamic_cast<Bullet*>(obj->second.get()) };

		bullet->setFricCoef(fricCoef);
		bullet->setForceAmount(forceAmount);
		bullet->setDamage(damage);
		bullet->setForce({ bullet->getForceAmount() * cos(angle(i)),
			bullet->getForceAmount() * sin(angle(i)), 0.0f });
		bullet->setVel(bullet->getForce());
		bullet->setVol(vol);
		bullet->setCol(col);
	}
}

void Judas::createBullet(float value, float fricCoef, float forceAmount, float damage, 
	const Color& col, const Vector& vol)
{
	const auto& obj{ objMgr->addObject<Bullet>(Obj::ENEMY_BULLET, Tex::ENEMY_BULLET, objPos) };
	const auto& bullet{ dynamic_cast<Bullet*>(obj->second.get()) };

	bullet->setFricCoef(fricCoef);
	bullet->setForceAmount(forceAmount);
	bullet->setDamage(damage);
	bullet->setForce({ bullet->getForceAmount() * cos(angle(value)),
		bullet->getForceAmount() * sin(angle(value)), 0.0f });
	bullet->setVel(bullet->getForce());
	bullet->setVol(vol);
	bullet->setCol(col);
}
