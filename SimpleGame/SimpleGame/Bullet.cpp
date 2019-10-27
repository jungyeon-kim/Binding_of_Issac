#include "stdafx.h"
#include "Bullet.h"
#include "Physics.h"
#include "Renderer.h"
#include "GameController.h"
#include "Player.h"

using namespace std;

Bullet::Bullet()
{
	init();
}

Bullet::Bullet(const Vector& pos, const Vector& vel)
{
	init(pos, vel);
}

Bullet::~Bullet()
{
}

void Bullet::init()
{
	gameCon = GameController::getInstance();

	forceAmount = 8;
	addForce();
	fricCoef = 1;
	objForce;				// No initialize for addForce()
	objPos = { 0, 0, 0 };
	objVel = { 0, 0, 0 };
	objAcc = { 0, 0, 0 };
	objVol = { meter() / 8, meter() / 8, 0 };
	objCol = { 0.5, 1, 0.5, 0 };
	objMass = 1;
}

void Bullet::init(const Vector& pos, const Vector& vel)
{
	gameCon = GameController::getInstance();

	forceAmount = 8;
	addForce();
	fricCoef = 1;
	objForce;				// No initialize for addForce()
	objPos = pos;
	objVel = objForce + vel;
	objAcc = { 0, 0, 0 };
	objVol = { meter() / 8, meter() / 8, 0 };
	objCol = { 0.5, 1, 0.5, 0 };
	objMass = 1;
}


void Bullet::update(float eTime)
{
	objForce = { 0, 0, 0 };

	physics->calcAcc(objAcc, objForce, objMass);
	physics->calcVel(objVel, objAcc, eTime);
	physics->calcFric(objVel, objMass, fricCoef, eTime);
	physics->calcPos(objPos, objVel, eTime);
}

void Bullet::render()
{
	renderer->DrawSolidRect(objPos.x, objPos.y, objPos.z, objVol.x,
		objCol.r, objCol.g, objCol.b, objCol.a);
}

void Bullet::addForce()
{
	if (gameCon->getShoot().up) objForce.y += forceAmount;
	else if (gameCon->getShoot().down) objForce.y -= forceAmount;
	if (gameCon->getShoot().left) objForce.x -= forceAmount;
	else if (gameCon->getShoot().right) objForce.x += forceAmount;
}