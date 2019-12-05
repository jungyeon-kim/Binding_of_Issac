#include "stdafx.h"
#include "Player.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"
#include "GameController.h"

using namespace std;

Player::Player(const Vector & pos)
{
	init(pos);
}

Player::~Player()
{
}

void Player::init(const Vector& pos)
{
	gameCon = GameController::getInstance();
	coolTime = make_unique<map<Skill, float>>();
	period = make_unique<map<Skill, float>>();

	texID = texture->getTexture(Tex::ISAC);
	maxHP = 100.0f;
	damage = 0.0f;

	forceAmount = 20.0f;
	fricCoef = 0.8f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(), meter(), meter() };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;

	setCoolTime();
}

void Player::update(float eTime)
{
	objForce = { 0.0f, 0.0f, 0.0f };
	addForce();

	// update Physics
	objAcc = physics->getAcc(objAcc, objForce, objMass);
	if (physics->getScalar(objVel) < MAX_SPEED) objVel = physics->getVel(objVel, objAcc, eTime);
	objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
	objPos = physics->getPos(objPos, objVel, objAcc, eTime);

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
	static int i{};
	renderer->DrawTextureRectAnim(objPos, objVol, objCol, texID, 10, 4, i, 0);
	++i = i % 10;
	//renderer->DrawTextureRect(objPos, objVol, objCol, texID);
	renderer->DrawSolidRectGauge(objPos, { 0.0f, meter(0.6), 0.0f }, { meter(), meter(0.15), 0.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f }, 100.0f);
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
