#include "stdafx.h"
#include "Bullet.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"

using namespace std;

Bullet::Bullet(const Vector& pos)
{
	cout << "Bullet:: Bullet Class can not create by this constructor. \n";
	assert(0);
}

Bullet::Bullet(Tex texID, const Vector& pos)
{
	init(texID, pos);
}

Bullet::~Bullet()
{
}

void Bullet::init(const Vector& pos)
{
	maxHP = 1.0f;
	currHP = maxHP;
	damage = 1000.0f;

	forceAmount = 8.0f;
	fricCoef = 1.0f;
	objForce;
	objPos = pos;
	objVel = objForce;
	objAcc;
	objVol = { meter(0.25f), meter(0.25f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 0.1f;
}

void Bullet::init(Tex texID, const Vector& pos)
{
	init(pos);

	this->texID.emplace_back(texMgr->getTexture(texID));
	this->texID.emplace_back(texMgr->getTexture(Tex::P_BLOOD3));
}

void Bullet::update(float eTime)
{
	GameActor::update(eTime);

	if (currHP > 0.0f && physics->getScalar(objVel))
	{
		physics->update(*this, eTime);
	}
	else
	{
		if (getEnableCollision()) setEnableCollision(false);
		doAnimCycle(3, 4, 4, 0);
	}
}

void Bullet::render()
{
	GameObj::render();

	if (currHP > 0.0f && physics->getScalar(objVel))
	{
		renderer->DrawTextureRect(objPos, objVol, objCol, texID[0]);
	}
	else
	{
		static const Vector& texVol{ objVol.x * 3.0f, objVol.y * 3.0f, objVol.z };
		static const Color& texCol{ 0.0f, 0.0f, 0.0f, 1.0f };
		renderer->DrawTextureRectAnim(objPos, texVol, texCol, texID[1], 4, 4, currAnimX[0], currAnimY[0]);
	}
}

void Bullet::addForce()
{
}

bool Bullet::isReadyToDestroy()
{
	return (currHP <= 0.0f || !physics->getScalar(objVel)) && onAnimEnded(0);
}
