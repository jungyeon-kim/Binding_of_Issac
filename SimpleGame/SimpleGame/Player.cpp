#include "stdafx.h"
#include "Player.h"
#include "Renderer.h"
#include "GameController.h"
#include "Physics.h"

using namespace std;

Player::Player()
{
	init();
}

Player::~Player()
{
}

void Player::init()
{
	forceAmount = 20;
	fricCoef = 1;
	objForce = { 0, 0, 0 };
	objPos = { 0, 0, 0 };
	objVol = { meter(), meter(), meter() };
	objVel = { 0, 0, 0 };
	objCol = { 0.5, 0.5, 0, 0 };
	objMass = 1;

	physics = make_unique<Physics>();
}

void Player::update(float eTime)
{
	addForce(eTime);

	physics->calcAcc(objAcc, objForce, objMass);
	physics->calcVel(objVel, objAcc, eTime);
	physics->calcFric(objVel, objMass, fricCoef, eTime);
	physics->calcPos(objPos, objVel, eTime);
}

void Player::render()
{
	renderer->DrawSolidRect(objPos.x, objPos.y, objPos.z, objVol.x,
		objCol.r, objCol.g, objCol.b, objCol.a);
}

void Player::addForce(float eTime)
{
	objForce = { 0, 0, 0 };

	if (gameCon->getDir().up) objForce.y += forceAmount;
	if (gameCon->getDir().down) objForce.y -= forceAmount;
	if (gameCon->getDir().left) objForce.x -= forceAmount;
	if (gameCon->getDir().right) objForce.x += forceAmount;
}
