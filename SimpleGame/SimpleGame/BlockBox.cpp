#include "stdafx.h"
#include "BlockBox.h"
#include "TexMgr.h"
#include "Renderer.h"
#include "Physics.h"


BlockBox::BlockBox(const Vector& pos)
{
	init(pos);
}

BlockBox::BlockBox(const Vector & pos, Tex texID)
{
	init(pos, texID);
}

BlockBox::~BlockBox()
{
}

void BlockBox::init(const Vector& pos)
{
	forceAmount;
	fricCoef = numeric_limits<float>::max();
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.95f), meter(0.95f), meter(0.95f) };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;

	debugCol = { 1.0f, 0.0f, 0.0f, 0.0f };
}

void BlockBox::init(const Vector& pos, Tex texID)
{
	init(pos);

	this->texID.emplace_back(texMgr->getTexture(texID));

	if (texID == Tex::BLOCKBOX_ROCK)
		objCol = { 
		static_cast<float>(uid(dre) / 100.0f), 
		static_cast<float>(uid(dre) / 100.0f),
		static_cast<float>(uid(dre) / 100.0f),
		1.0f 
	};
}

void BlockBox::update(float eTime)
{
	GameObj::update(eTime);

	objForce = { 0.0f, 0.0f, 0.0f };
	addForce();

	// update Physics
	objAcc = physics->getAcc(objAcc, objForce, objMass);
	objVel = physics->getVel(objVel, objAcc, eTime);
	objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
	objPos = physics->getPos(objPos, objVel, objAcc, eTime);
}

void BlockBox::render()
{
	if (!texID.empty())
	{
		static const Vector& texVol{ objVol * 1.1f };
		renderer->DrawTextureRect(objPos, texVol, objCol, texID[0]);
	}

	GameObj::render();		// 셰이더가 z축 기준으로 렌더링 되게 바뀌면 맨 앞에서 호출할 예정
}

void BlockBox::addForce()
{
}

bool BlockBox::isReadyToDestroy()
{
	return false;
}
