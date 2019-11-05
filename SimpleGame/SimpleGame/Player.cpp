#include "stdafx.h"
#include "Player.h"
#include "Physics.h"
#include "Renderer.h"
#include "GameController.h"

using namespace std;

int Player::texID{};

Player::Player(const Vector& pos)
{
	init(pos);
}

Player::~Player()
{
}

void Player::init(const Vector& pos)
{
	if (!texID) texID = renderer->GenPngTexture("./textures/TestImg.png");

	gameCon = GameController::getInstance();
	coolTime = make_unique<map<string, float>>();
	period = make_unique<map<string, float>>();

	setCoolTime();

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
	for (auto& cool : *coolTime)
		if (cool.second)
		{
			cool.second -= eTime;
			if (cool.second < 0) cool.second = 0;
		}

	objForce = { 0, 0, 0 };
	addForce();

	physics->calcAcc(objAcc, objForce, objMass);
	if (physics->calcScalar(objVel) < 8) physics->calcVel(objVel, objAcc, eTime);
	physics->calcFric(objVel, objMass, fricCoef, eTime);
	physics->calcPos(objPos, objVel, eTime);
}

void Player::render()
{
	renderer->DrawTextureRect(objPos, objVol, objCol, texID);
}

void Player::addForce()
{
	if (gameCon->getDir().up) objForce.y += forceAmount;
	if (gameCon->getDir().down) objForce.y -= forceAmount;
	if (gameCon->getDir().left) objForce.x -= forceAmount;
	if (gameCon->getDir().right) objForce.x += forceAmount;
}

bool Player::isEndCoolTime(const string& name) const
{
	return !(*coolTime)[name];
}

void Player::resetCoolTime(const string& name)
{
	(*coolTime)[name] = (*period)[name];
}

void Player::setCoolTime()
{
	coolTime->emplace("shoot", 0);
	period->emplace("shoot", 0.4);
}
