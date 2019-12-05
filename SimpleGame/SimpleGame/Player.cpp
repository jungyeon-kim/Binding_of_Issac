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

	texID.emplace_back(texture->getTexture(Tex::ISAC_BODY));
	texID.emplace_back(texture->getTexture(Tex::ISAC_HEAD));
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
	GameActor::update(eTime);

	objForce = { 0.0f, 0.0f, 0.0f };
	addForce();

	// update Physics
	objAcc = physics->getAcc(objAcc, objForce, objMass);
	objVel = physics->getVel(objVel, objAcc, eTime, MAX_VEL);
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
	if (!(++animCycle % 10))
	{
		++nextHeadAnimX %= 2;
		++nextBodyAnimX %= 10;
		animCycle = 0;
	}
	if (objCol.a != 1.0f) ++alphaCnt;
	if (alphaCnt > 20)
	{
		objCol.a = 1.0f;
		alphaCnt = 0.0f;
	}
}

void Player::render()
{
	const Vector& bodyPos{ objPos.x, objPos.y - meter(0.2), objPos.z };
	const Vector& bodyVol{ objVol.x / 2.0f, objVol.y / 2.0f, objVol.z };
	const Vector& headPos{ objPos.x, objPos.y + meter(0.2), objPos.z };
	const Vector& headVol{ objVol.x / 1.3f, objVol.y / 1.4f, objVol.z };

	if (!gameCon->isMove()) renderer->DrawTextureRectAnim(bodyPos, bodyVol, objCol, texID[0], 10, 4, 0, 1);
	else if (gameCon->getDir().up) renderer->DrawTextureRectAnim(bodyPos, bodyVol, objCol, texID[0], 10, 4, nextBodyAnimX, 0);
	else if (gameCon->getDir().down) renderer->DrawTextureRectAnim(bodyPos, bodyVol, objCol, texID[0], 10, 4, nextBodyAnimX, 1);
	else if (gameCon->getDir().left) renderer->DrawTextureRectAnim(bodyPos, bodyVol, objCol, texID[0], 10, 4, nextBodyAnimX, 2);
	else if (gameCon->getDir().right) renderer->DrawTextureRectAnim(bodyPos, bodyVol, objCol, texID[0], 10, 4, nextBodyAnimX, 3);
	if (!gameCon->isShoot()) renderer->DrawTextureRectAnim(headPos, headVol, objCol, texID[1], 2, 4, 0, 1);
	else if (gameCon->getShoot().up) renderer->DrawTextureRectAnim(headPos, headVol, objCol, texID[1], 2, 4, nextHeadAnimX, 0);
	else if (gameCon->getShoot().down) renderer->DrawTextureRectAnim(headPos, headVol, objCol, texID[1], 2, 4, nextHeadAnimX, 1);
	else if (gameCon->getShoot().left) renderer->DrawTextureRectAnim(headPos, headVol, objCol, texID[1], 2, 4, nextHeadAnimX, 2);
	else if (gameCon->getShoot().right) renderer->DrawTextureRectAnim(headPos, headVol, objCol, texID[1], 2, 4, nextHeadAnimX, 3);

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
