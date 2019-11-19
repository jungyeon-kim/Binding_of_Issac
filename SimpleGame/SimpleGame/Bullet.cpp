#include "stdafx.h"
#include "Bullet.h"
#include "Physics.h"
#include "Renderer.h"
#include "GameController.h"
#include "TexMgr.h"

using namespace std;

Bullet::Bullet(Obj name, const Vector& pos)
{
	init(name, pos);
}

Bullet::Bullet(Obj name, const Vector& pos, const Vector& vel)
{
	init(name, pos, vel);
}

Bullet::~Bullet()
{
}

void Bullet::init(Obj name, const Vector& pos)
{
	gameCon = GameController::getInstance();

	texID = texture->getTexture(name);

	forceAmount = 8.0f;
	addForce();
	fricCoef = 1.0f;
	objForce;				// No initialize for addForce()
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter() / 2, meter() / 2, 0 };
	objCol = { 0.5f, 1.0f, 0.5f, 1.0f };
	objMass = 1.0f;
}

void Bullet::init(Obj name, const Vector& pos, const Vector& vel)
{
	init(name, pos);
	objVel = objForce + vel;
}

void Bullet::update(float eTime)
{
	objForce = { 0.0f, 0.0f, 0.0f };

	// update Physics
	physics->calcAcc(objAcc, objForce, objMass);
	physics->calcVel(objVel, objAcc, eTime);
	physics->calcFric(objVel, objMass, fricCoef, eTime);
	physics->calcPos(objPos, objVel, objAcc, eTime);
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