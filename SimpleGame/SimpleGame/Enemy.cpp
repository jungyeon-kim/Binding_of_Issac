#include "stdafx.h"
#include "Enemy.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"

Enemy::Enemy(const Vector& pos)
{
	init(pos);
}

Enemy::~Enemy()
{
}

void Enemy::init(const Vector& pos)
{
	texID = texture->getTexture(Tex::TEST);

	forceAmount = 10.0f;
	fricCoef = 0.8f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(2), meter(2), meter() };
	objCol = { 0.5f, 0.7f, 0.0f, 1.0f };
	objMass = 2.0f;
}

void Enemy::update(float eTime)
{
	objForce = { 0.0f, 0.0f, 0.0f };

	// update Physics
	objAcc = physics->getAcc(objAcc, objForce, objMass);
	objVel = physics->getVel(objVel, objAcc, eTime);
	objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
	objPos = physics->getPos(objPos, objVel, objAcc, eTime);
}

void Enemy::render()
{
	renderer->DrawTextureRect(objPos, objVol, objCol, texID);
}

void Enemy::addForce()
{
}
