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
	maxCoolTime = make_unique<map<Skill, float>>();
	currCoolTime = make_unique<map<Skill, float>>();

	texID = texture->getTexture(Tex::ISAC);
	maxHP = 100.0f;
	currHP = maxHP;
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
	for (auto& cool : *currCoolTime)
		if (cool.second)
		{
			cool.second -= eTime;
			if (cool.second < 0) cool.second = 0;
		}

	// update Rendering Data
	if (!(++animCycle % 10)) ++nextAnimX %= 10;
	if (objCol.a != 1.0f) ++alphaCnt;
	if (alphaCnt > 20)
	{
		objCol.a = 1.0f;
		alphaCnt = 0.0f;
	}
}

void Player::render()
{
	renderer->DrawTextureRectAnim(objPos, objVol, objCol, texID, 10, 4, nextAnimX, 0);
	renderer->DrawSolidRectGauge(objPos, { 0.0f, meter(0.7), 0.0f }, { objVol.x, meter(0.15), 0.0f },
		{ 0.8f, 0.8f, 0.8f, 0.8f }, 100.0f);
	renderer->DrawSolidRectGauge(objPos, { 0.0f, meter(0.7), 0.0f }, { objVol.x, meter(0.15), 0.0f },
		{ 1.0f, 0.0f, 0.0f, 0.8f }, (currHP / maxHP) * 100.0f);
}

void Player::addForce()
{
	if (gameCon->getDir().up) objForce.y += forceAmount;
	if (gameCon->getDir().down) objForce.y -= forceAmount;
	if (gameCon->getDir().left) objForce.x -= forceAmount;
	if (gameCon->getDir().right) objForce.x += forceAmount;
}

void Player::takeDamage(float damage)
{
	GameActor::takeDamage(damage);

	objCol.a = 0.2f;
}

bool Player::isEndCoolTime(Skill name) const
{
	return !(*currCoolTime)[name];
}

void Player::resetCoolTime(Skill name)
{
	(*currCoolTime)[name] = (*maxCoolTime)[name];
}

void Player::setCoolTime()
{
	currCoolTime->emplace(Skill::SHOOT, 0.0f);
	maxCoolTime->emplace(Skill::SHOOT, 0.4f);
}
