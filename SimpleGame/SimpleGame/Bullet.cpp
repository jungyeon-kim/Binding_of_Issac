#include "stdafx.h"
#include "Bullet.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"
#include "GameController.h"

using namespace std;

Bullet::Bullet(const Vector& pos)
{
	init(pos);
}

Bullet::Bullet(const Vector& pos, const Vector& vel)
{
	init(pos, vel);
}

Bullet::~Bullet()
{
}

void Bullet::init(const Vector& pos)
{
	gameCon = GameController::getInstance();

	texID = texture->getTexture(Tex::TEST);
	maxHP = 1.0f;
	damage = 25.0f;

	forceAmount = 11.0f;
	fricCoef = 1.0f;
	addForce();
	objForce;				// No initialize for addForce()
	objPos = pos;
	objVel = objForce;
	objAcc;
	objVol = { meter(0.25), meter(0.25), meter(0.25) };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 0.2f;
}

void Bullet::init(const Vector& pos, const Vector& vel)
{
	init(pos);
	objVel = objForce + vel;
}

void Bullet::update(float eTime)
{
	objForce = { 0.0f, 0.0f, 0.0f };

	// update Physics
	objAcc = physics->getAcc(objAcc, objForce, objMass);
	objVel = physics->getVel(objVel, objAcc, eTime);
	objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
	objPos = physics->getPos(objPos, objVel, objAcc, eTime);
}

void Bullet::render()
{
	renderer->DrawTextureRect(objPos, objVol, objCol, texID);
}

void Bullet::addForce()
{
	if (gameCon->getShoot().up) objForce.y += forceAmount;
	else if (gameCon->getShoot().down) objForce.y -= forceAmount;
	else if (gameCon->getShoot().left) objForce.x -= forceAmount;
	else if (gameCon->getShoot().right) objForce.x += forceAmount;
}