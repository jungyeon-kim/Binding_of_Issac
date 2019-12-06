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
	gameCon = GameController::getInstance();

	texID.emplace_back(texture->getTexture(Tex::BASIC_BULLET));
	maxHP = 1.0f;
	currHP = maxHP;
	damage = 25.0f;

	forceAmount = 10.0f;
	fricCoef = 1.0f;
	addForce();
	objForce;				// No initialize for addForce()
	objPos = pos;
	objVel = objForce;
	objAcc;
	objVol = { meter(0.25), meter(0.25), meter(0.25) };
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

	objForce = { 0.0f, 0.0f, 0.0f };

	// update Physics
	objAcc = physics->getAcc(objAcc, objForce, objMass);
	objVel = physics->getVel(objVel, objAcc, eTime);
	objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
	objPos = physics->getPos(objPos, objVel, objAcc, eTime);
}

void PlayerBullet::render()
{
	renderer->DrawTextureRect(objPos, objVol, objCol, texID[0]);

	GameObj::render();		// 셰이더가 z축 기준으로 렌더링 되게 바뀌면 맨 앞에서 호출할 예정
}

void PlayerBullet::addForce()
{
	if (gameCon->getShoot().up) objForce.y += forceAmount;
	else if (gameCon->getShoot().down) objForce.y -= forceAmount;
	else if (gameCon->getShoot().left) objForce.x -= forceAmount;
	else if (gameCon->getShoot().right) objForce.x += forceAmount;
}