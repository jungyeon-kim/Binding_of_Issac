#include "stdafx.h"
#include "Player.h"
#include "Physics.h"
#include "Renderer.h"
#include "GameController.h"
#include "TexMgr.h"

using namespace std;

Player::Player(Tex name, const Vector & pos)
{
	init(name, pos);
}

Player::~Player()
{
}

void Player::init(Tex name, const Vector& pos)
{
	gameCon = GameController::getInstance();
	coolTime = make_unique<map<Skill, float>>();
	period = make_unique<map<Skill, float>>();

	texID = texture->getTexture(name);

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
	objForce = { 0.0f, 0.0f, 0.0f };
	addForce();

	// update Physics
	physics->calcAcc(objAcc, objForce, objMass);
	if (physics->calcScalar(objVel) < MAX_SPEED) physics->calcVel(objVel, objAcc, eTime);
	physics->calcFric(objVel, objMass, fricCoef, eTime);
	physics->calcPos(objPos, objVel, objAcc, eTime);

	// update CoolTime
	for (auto& cool : *coolTime)
		if (cool.second)
		{
			cool.second -= eTime;
			if (cool.second < 0) cool.second = 0;
		}
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

bool Player::isEndCoolTime(Skill name) const
{
	return !(*coolTime)[name];
}

void Player::resetCoolTime(Skill name)
{
	(*coolTime)[name] = (*period)[name];
}

void Player::setCoolTime()
{
	coolTime->emplace(Skill::SHOOT, 0.0f);
	period->emplace(Skill::SHOOT, 0.4f);
}