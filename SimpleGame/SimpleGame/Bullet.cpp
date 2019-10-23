#include "stdafx.h"
#include "Bullet.h"
#include "Physics.h"
#include "Renderer.h"
#include "GameController.h"

Bullet::Bullet()
{
	init();
}

Bullet::~Bullet()
{
}

void Bullet::init()
{
	gameCon = GameController::getInstance();

	forceAmount = 20;
	fricCoef = 0;
	objForce = { 0, 0, 0 };
	objPos = { 0, 0, 0 };
	objVol = { meter() / 4, meter() / 4, meter() / 4 };
	objVel = { 0, 0, 0 };
	objCol = { 0.5, 0.5, 0, 0 };
	objMass = 1;

	addForce();
}

void Bullet::update(float eTime)
{
	physics->calcAcc(objAcc, objForce, objMass);
	physics->calcVel(objVel, objAcc, eTime);
	//physics->calcFric(objVel, objMass, fricCoef, eTime);
	physics->calcPos(objPos, objVel, eTime);
}

void Bullet::render()
{
	renderer->DrawSolidRect(objPos.x, objPos.y, objPos.z, objVol.x,
		objCol.r, objCol.g, objCol.b, objCol.a);
}

void Bullet::addForce()
{
	objForce = { 0, 0, 0 };

	if (gameCon->getShoot().up) objForce.y += forceAmount;
	else if (gameCon->getShoot().down) objForce.y -= forceAmount;
	if (gameCon->getShoot().left) objForce.x -= forceAmount;
	else if (gameCon->getShoot().right) objForce.x += forceAmount;
}
