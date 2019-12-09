#include "stdafx.h"
#include "PlayerBullet.h"
#include "Physics.h"
#include "Renderer.h"
#include "TexMgr.h"
#include "GameController.h"

using namespace std;

PlayerBullet::PlayerBullet(const Vector& pos)
{
	init(pos);
}

PlayerBullet::PlayerBullet(const Vector& pos, const Vector& vel)
{
	init(pos, vel);
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::init(const Vector& pos)
{
	texID.emplace_back(texMgr->getTexture(Tex::PLAYER_BULLET));
	texID.emplace_back(texMgr->getTexture(Tex::P_BLOOD3));

	maxHP = 1.0f;
	currHP = maxHP;
	damage = 10.0f;

	forceAmount = 10.0f;
	fricCoef = 1.0f;
	addForce();
	objForce;				// No initialize for addForce()
	objPos = pos;
	objVel = objForce;
	objAcc;
	objVol = { meter(0.25f), meter(0.25f), meter(0.25f) };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 0.2f;
}

void PlayerBullet::init(const Vector& pos, const Vector& vel)
{
	init(pos);
	objVel = objForce + vel;
}

void PlayerBullet::update(float eTime)
{
	GameActor::update(eTime);

	if (currHP > 0.0f && physics->getScalar(objVel))
	{
		objForce = { 0.0f, 0.0f, 0.0f };

		// Update Physics
		objAcc = physics->getAcc(objAcc, objForce, objMass);
		objVel = physics->getVel(objVel, objAcc, eTime);
		objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
		objPos = physics->getPos(objPos, objVel, objAcc, eTime);
	}
	else
	{
		if (getEnableCollision()) setEnableCollision(false);
		doAnimCycle(3, 4, 4, 0);
	}
}

void PlayerBullet::render()
{
	if (currHP > 0.0f && physics->getScalar(objVel))
	{
		renderer->DrawTextureRect(objPos, objVol, objCol, texID[0]);
	}
	else
	{
		static const Vector& texVol{ objVol.x * 3.0f, objVol.y * 3.0f, objVol.z };
		static const Color& texCol{ 0.0f, 0.0f, 0.0f, 1.0f };
		renderer->DrawTextureRectAnim(objPos, texVol, texCol, texID[1], 4, 4, nextAnimX[0], nextAnimY[0]);
	}

	GameActor::render();		// 셰이더가 z축 기준으로 렌더링 되게 바뀌면 맨 앞에서 호출할 예정
}

void PlayerBullet::addForce()
{
	if (gameCon->getShoot().up) objForce.y += forceAmount;
	else if (gameCon->getShoot().down) objForce.y -= forceAmount;
	else if (gameCon->getShoot().left) objForce.x -= forceAmount;
	else if (gameCon->getShoot().right) objForce.x += forceAmount;
}

bool PlayerBullet::isReadyToDestroy()
{
	return (currHP <= 0.0f || !physics->getScalar(objVel)) && onAnimEnded(0);
}
