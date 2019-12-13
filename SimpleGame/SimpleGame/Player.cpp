#include "stdafx.h"
#include "Player.h"
#include "GameController.h"
#include "ObjMgr.h"
#include "TexMgr.h"
#include "Bullet.h"
#include "Physics.h"
#include "Renderer.h"

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
	maxCoolTime = make_unique<map<Skill, float>>();
	currCoolTime = make_unique<map<Skill, float>>();

	texID.emplace_back(texMgr->getTexture(Tex::PLAYER_BODY));
	texID.emplace_back(texMgr->getTexture(Tex::PLAYER_HEAD));

	maxHP = 100.0f;
	currHP = maxHP;
	damage = 0.0f;

	forceAmount = 20.0f;
	fricCoef = 0.8f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.7f), meter(0.7f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;

	setCoolTime();
}

void Player::update(float eTime)
{
	GameActor::update(eTime);

	physics->update(*this, eTime, MAX_VEL);

	// Decide whether to spawn a Bullet from Player
	if (gameCon->isShoot() && isEndCoolTime(Skill::SHOOT))
	{
		createBullet();
		resetCoolTime(Skill::SHOOT);
	}

	// Update Cycle
	doAnimCycle(10, 10, 1, 0);
	doAnimCycle(10, 2, 1, 1);

	for (auto& cool : *currCoolTime)
		if (cool.second)
		{
			cool.second -= eTime;
			if (cool.second < 0) cool.second = 0;
		}

	if (objCol.a != 1.0f)
		if (!(++alphaCnt % 20))
		{
			objCol.a = 1.0f;
			alphaCnt = 0;
		}

	if (!canDamaged)
		if (!(++canDamagedCycle % 60))
		{
			canDamaged = true;
			canDamagedCycle = 0;
		}
}

void Player::render()
{
	GameActor::render();

	const Vector& bodyTexPos{ objPos.x, objPos.y - meter(0.3f), objPos.z };
	const Vector& headTexPos{ objPos.x, objPos.y + meter(0.125f), objPos.z };
	static const Vector& bodyTexVol{ objVol.x / 1.5f, objVol.y / 1.5f, objVol.z };
	static const Vector& headTexVol{ objVol.x * 1.1f, objVol.y, objVol.z };

	if (!gameCon->isMove()) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, 0, 1, true, 1.0f);
	else if (gameCon->getDir().left) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, nextAnimX[0], 2, true, 1.0f);
	else if (gameCon->getDir().right) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, nextAnimX[0], 3, true, 1.0f);
	else if (gameCon->getDir().up) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, nextAnimX[0], 0, true, 1.0f);
	else if (gameCon->getDir().down) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, nextAnimX[0], 1, true, 1.0f);
	if (!gameCon->isShoot()) renderer->DrawTextureRectAnim(headTexPos, headTexVol, objCol, texID[1], 2, 4, 0, 1);
	else if (gameCon->getShoot().left) renderer->DrawTextureRectAnim(headTexPos, headTexVol, objCol, texID[1], 2, 4, nextAnimX[1], 2);
	else if (gameCon->getShoot().right) renderer->DrawTextureRectAnim(headTexPos, headTexVol, objCol, texID[1], 2, 4, nextAnimX[1], 3);
	else if (gameCon->getShoot().up) renderer->DrawTextureRectAnim(headTexPos, headTexVol, objCol, texID[1], 2, 4, nextAnimX[1], 0);
	else if (gameCon->getShoot().down) renderer->DrawTextureRectAnim(headTexPos, headTexVol, objCol, texID[1], 2, 4, nextAnimX[1], 1);
}

void Player::addForce()
{
	if (gameCon->getDir().up) objForce.y += forceAmount;
	if (gameCon->getDir().down) objForce.y -= forceAmount;
	if (gameCon->getDir().left) objForce.x -= forceAmount;
	if (gameCon->getDir().right) objForce.x += forceAmount;
}

void Player::takeDamage(float damage, const GameActor& attacker)
{
	if (attacker.getEnableCollision() && canDamaged)
	{
		currHP -= damage;
		objCol.a = 0.2f;
		canDamaged = false;
	}
}

bool Player::isReadyToDestroy()
{
	return false;
}

void Player::createBullet()
{
	const Vector& bulletPos{ objPos.x, objPos.y + meter(0.125f), objPos.z };
	const auto& obj{ objMgr->addObject<Bullet>(Obj::PLAYER_BULLET, Tex::PLAYER_BULLET, bulletPos) };
	const auto& bullet{ dynamic_cast<Bullet*>(obj->second.get()) };

	if (gameCon->getShoot().up) bullet->setForce({ 0.0f, bullet->getForceAmount(), 0.0f });
	else if (gameCon->getShoot().down) bullet->setForce({ 0.0f, -bullet->getForceAmount(), 0.0f });
	else if (gameCon->getShoot().left) bullet->setForce({ -bullet->getForceAmount(), 0.0f, 0.0f });
	else if (gameCon->getShoot().right) bullet->setForce({ bullet->getForceAmount(), 0.0f, 0.0f });
	bullet->setVel(bullet->getForce() + objVel);
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
