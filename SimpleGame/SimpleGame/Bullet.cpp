#include "stdafx.h"
#include "Bullet.h"
#include "Physics.h"
#include "Renderer.h"
#include "GameController.h"

using namespace std;

int Bullet::TEX_ID{};

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
	if (!TEX_ID) TEX_ID = renderer->GenPngTexture("./textures/TestImg.png");

	gameCon = GameController::getInstance();

	forceAmount = 8.0f;
	addForce();
	fricCoef = 1.0f;
	objForce;				// No initialize for addForce()
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter() / 8, meter() / 8, 0 };
	objCol = { 0.5f, 1.0f, 0.5f, 1.0f };
	objMass = 1.0f;
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
	physics->calcAcc(objAcc, objForce, objMass);
	physics->calcVel(objVel, objAcc, eTime);
	physics->calcFric(objVel, objMass, fricCoef, eTime);
	physics->calcPos(objPos, objVel, objAcc, eTime);
}

void Bullet::render()
{
	renderer->DrawTextureRect(objPos, objVol, objCol, TEX_ID);
}

void Bullet::addForce()
{
	if (gameCon->getShoot().up) objForce.y += forceAmount;
	else if (gameCon->getShoot().down) objForce.y -= forceAmount;
	else if (gameCon->getShoot().left) objForce.x -= forceAmount;
	else if (gameCon->getShoot().right) objForce.x += forceAmount;
}