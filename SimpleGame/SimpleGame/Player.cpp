#include "stdafx.h"
#include "Player.h"
#include "GameController.h"

Player::Player()
{
	objForce = { 0, 0, 0 };
	objPos = { 0, 0, 0 };
	objVol = { meter(), meter(), meter() };
	objVel = { 0, 0, 0 };
	objCol = { 1, 0, 0, 0 };
	objMass = 1;

	forceAmount = 3;

	gameController = GameController::getInstance();
}

Player::~Player()
{
}

void Player::update(float eTime)
{
	objForce = { 0, 0, 0 };

	if (gameController->getDir().up) objForce.y += forceAmount;
	if (gameController->getDir().down) objForce.y -= forceAmount;
	if (gameController->getDir().left) objForce.x -= forceAmount;
	if (gameController->getDir().right) objForce.x += forceAmount;

	addForce(eTime);

	objPos = { getPos().x + getVel().x * eTime * meter(),
		getPos().y + getVel().y * eTime * meter(),
		getPos().z + getVel().z * eTime * meter() };
}
