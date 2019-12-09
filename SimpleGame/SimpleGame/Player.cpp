#include "stdafx.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"
#include "GameController.h"
#include "ObjMgr.h"

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
	objVol = { meter(0.7f), meter(0.7f), meter(0.7f) };
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

	// Decide whether to spawn a Bullet from Player
	if (gameCon->isShoot() && isEndCoolTime(Skill::SHOOT))
	{
		objMgr->addObject<PlayerBullet>(Obj::PLAYER_BULLET, objPos, objVel);
		resetCoolTime(Skill::SHOOT);
	}

	// update CoolTime
	for (auto& cool : *currCoolTime)
		if (cool.second)
		{
			cool.second -= eTime;
			if (cool.second < 0) cool.second = 0;
		}

	// update Rendering Cycle
	doAnimCycle(10, 10, 0, 0);
	doAnimCycle(10, 2, 0, 1);

	if (objCol.a != 1.0f)
		if (!(++alphaCnt % 20))
		{
			objCol.a = 1.0f;
			alphaCnt = 0;
		}

	// update CanDamaged Cycle
	if (!canDamaged)
		if (!(++canDamagedCycle % 60))
		{
			canDamaged = true;
			canDamagedCycle = 0;
		}
}

void Player::render()
{
	const Vector& bodyTexPos{ objPos.x, objPos.y - meter(0.2f), objPos.z };
	const Vector& heaTexPos{ objPos.x, objPos.y + meter(0.2f), objPos.z };
	static const Vector& bodyTexVol{ objVol.x / 1.5f, objVol.y / 1.5f, objVol.z };
	static const Vector& headTexVol{ objVol.x * 1.1f, objVol.y, objVol.z };

	if (!gameCon->isMove()) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, 0, 1);
	else if (gameCon->getDir().up) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, nextAnimX[0], 0);
	else if (gameCon->getDir().down) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, nextAnimX[0], 1);
	else if (gameCon->getDir().left) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, nextAnimX[0], 2);
	else if (gameCon->getDir().right) renderer->DrawTextureRectAnim(bodyTexPos, bodyTexVol, objCol, texID[0], 10, 4, nextAnimX[0], 3);
	if (!gameCon->isShoot()) renderer->DrawTextureRectAnim(heaTexPos, headTexVol, objCol, texID[1], 2, 4, 0, 1);
	else if (gameCon->getShoot().up) renderer->DrawTextureRectAnim(heaTexPos, headTexVol, objCol, texID[1], 2, 4, nextAnimX[1], 0);
	else if (gameCon->getShoot().down) renderer->DrawTextureRectAnim(heaTexPos, headTexVol, objCol, texID[1], 2, 4, nextAnimX[1], 1);
	else if (gameCon->getShoot().left) renderer->DrawTextureRectAnim(heaTexPos, headTexVol, objCol, texID[1], 2, 4, nextAnimX[1], 2);
	else if (gameCon->getShoot().right) renderer->DrawTextureRectAnim(heaTexPos, headTexVol, objCol, texID[1], 2, 4, nextAnimX[1], 3);

	GameActor::render();		// 셰이더가 z축 기준으로 렌더링 되게 바뀌면 맨 앞에서 호출할 예정
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
