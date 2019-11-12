#include "stdafx.h"
#include "Player.h"
#include "Physics.h"
#include "Renderer.h"
#include "GameController.h"

using namespace std;

int Player::TEX_ID{};

Player::Player(const Vector& pos)
{
	init(pos);
}

Player::~Player()
{
}

void Player::init(const Vector& pos)
{
	if (!TEX_ID) TEX_ID = renderer->GenPngTexture("./textures/TestImg.png");

	gameCon = GameController::getInstance();
	coolTime = make_unique<map<string, float>>();
	period = make_unique<map<string, float>>();

	setCoolTime();

	forceAmount = 20.0f;
	fricCoef = 0.8f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(), meter(), meter() };
	objCol = { 0.5f, 0.7f, 0.0f, 1.0f };
	objMass = 1.0f;
}

void Player::update(float eTime)
{
	for (auto& cool : *coolTime)
		if (cool.second)
		{
			cool.second -= eTime;
			if (cool.second < 0) cool.second = 0;
		}

	objForce = { 0.0f, 0.0f, 0.0f };
	addForce();

	physics->calcAcc(objAcc, objForce, objMass);
	if (physics->calcScalar(objVel) < MAX_SPEED) physics->calcVel(objVel, objAcc, eTime);
	physics->calcFric(objVel, objMass, fricCoef, eTime);
	physics->calcPos(objPos, objVel, objAcc, eTime);
}

void Player::render()
{
	renderer->DrawTextureRect(objPos, objVol, objCol, TEX_ID);
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
	coolTime->emplace("shoot", 0.0f);
	period->emplace("shoot", 0.4f);
}
