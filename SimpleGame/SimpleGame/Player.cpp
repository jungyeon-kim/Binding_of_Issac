#include "stdafx.h"
#include "Player.h"
#include "Physics.h"
#include "Renderer.h"
#include "GameController.h"

using namespace std;

Player::Player(const Vector& pos)
{
	init(pos);
}

Player::~Player()
{
}

void Player::init(const Vector& pos)
{
	gameCon = GameController::getInstance();

	forceAmount = 15;
	fricCoef = 1;
	objForce = { 0, 0, 0 };
	objPos = pos;
	objVel = { 0, 0, 0 };
	objAcc = { 0, 0, 0 };
	objVol = { meter(), meter(), meter() };
	objCol = { 0.5, 0.7, 0, 1 };
	objMass = 1;
}

void Player::update(float eTime)
{
	objForce = { 0, 0, 0 };
	addForce();

	physics->calcAcc(objAcc, objForce, objMass);
	if (physics->calcScalar(objVel) < 8) physics->calcVel(objVel, objAcc, eTime);
	physics->calcFric(objVel, objMass, fricCoef, eTime);
	physics->calcPos(objPos, objVel, eTime);
}

void Player::render()
{
	renderer->DrawSolidRect(objPos.x, objPos.y, objPos.z, objVol.x,
		objCol.r, objCol.g, objCol.b, objCol.a);
}

void Player::addForce()
{
	if (gameCon->getDir().up) objForce.y += forceAmount;
	if (gameCon->getDir().down) objForce.y -= forceAmount;
	if (gameCon->getDir().left) objForce.x -= forceAmount;
	if (gameCon->getDir().right) objForce.x += forceAmount;
}
