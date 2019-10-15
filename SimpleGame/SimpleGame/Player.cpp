#include "stdafx.h"
#include "Player.h"
#include "Renderer.h"
#include "GameController.h"

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
	forceAmount = 3;
	objForce = { 0, 0, 0 };
	objPos = { 0, 0, 0 };
	objVol = { meter(), meter(), meter() };
	objVel = { 0, 0, 0 };
	objCol = { 1, 0, 0, 0 };
	objMass = 1;

	gameCon = GameController::getInstance();
	renderer = make_unique<Renderer>(wndSizeX, wndSizeY);
}

void Player::update(float eTime)
{
	calcPhysics(eTime);

	// pos = pos + vel * eTime
	objPos = { objPos.x + objVel.x * eTime * meter(),
		objPos.y + objVel.y * eTime * meter(),
		objPos.z + objVel.z * eTime * meter() };
}

void Player::render()
{
	renderer->DrawSolidRect(objPos.x, objPos.y, objPos.z, objVol.x,
		objCol.r, objCol.g, objCol.b, objCol.a);
}

void Player::calcPhysics(float eTime)
{
	objForce = { 0, 0, 0 };

	if (gameCon->getDir().up) objForce.y += forceAmount;
	if (gameCon->getDir().down) objForce.y -= forceAmount;
	if (gameCon->getDir().left) objForce.x -= forceAmount;
	if (gameCon->getDir().right) objForce.x += forceAmount;

	// acc = force / mass
	objAcc = { objForce.x / objMass, objForce.y / objMass, objForce.z / objMass };
	// vel = vel + acc * eTime
	objVel = { objVel.x + objAcc.x * eTime, objVel.y + objAcc.y * eTime, objVel.z + objAcc.z * eTime };
}
