#include "stdafx.h"
#include "ObjBox.h"
#include "TexMgr.h"
#include "SoundMgr.h"
#include "Physics.h"
#include "Renderer.h"

using namespace std;

ObjBox::ObjBox(const Vector& pos)
{
	cout << "ObjBox:: ObjBox Class can not create by this constructor. \n";
	assert(0);
}

ObjBox::ObjBox(TEX texID, const Vector& pos)
{
	init(texID, pos);
}

ObjBox::~ObjBox()
{
}

void ObjBox::init(const Vector& pos)
{
	maxHP = 30.0f;
	currHP = maxHP;
	damage = 0.0f;

	forceAmount;
	fricCoef = numeric_limits<float>::max();
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.95f), meter(0.95f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;
}

void ObjBox::init(TEX texID, const Vector& pos)
{
	init(pos);

	this->texID.emplace_back(texMgr->getTexture(texID));
	texType = texID;

	switch (texType)
	{
	case TEX::OBJBOX_ROCK:
		this->texID.emplace_back(texMgr->getTexture(TEX::P_EXPLOSION1));
		objCol = { urdCol(dre), urdCol(dre), urdCol(dre), 1.0f };
		break;
	}
}

void ObjBox::update(float eTime)
{
	GameActor::update(eTime);

	if (currHP > 0.0f)
	{
		physics->update(*this, eTime);
	}
	else
	{
		if (getEnableCollision())
		{
			soundMgr->PlayShortSound(soundMgr->getSound(SOUND::DESTROY_ROCK), false, 0.6f);
			setEnableCollision(false);
		}

		switch (texType)
		{
		case TEX::OBJBOX_ROCK:
			doAnimCycle(7, 10, 1, 1);
			break;
		}
	}
}

void ObjBox::render()
{
	GameActor::render();

	if (currHP > 0.0f)
	{
		static const Vector& texVol{ objVol * 1.1f };
		renderer->DrawTextureRect(objPos, texVol, objCol, texID[0]);
	}
	else
	{
		static const Vector& texVol{ objVol.x * 2.0f, objVol.y * 2.0f, objVol.z };

		switch (texType)
		{
		case TEX::OBJBOX_ROCK:
			renderer->DrawTextureRectAnim(objPos, texVol, objCol, texID[1], 10, 1, currAnimX[1], currAnimY[1]);
			break;
		}
	}
}

void ObjBox::addForce()
{
}

void ObjBox::takeDamage(float damage, OBJ attackerType, const GameActor& attacker)
{
	if (attacker.getEnableCollision() && damage > 0.0f)
	{
		if(attackerType == OBJ::PLAYER_BULLET) currHP -= damage;
	}
}

bool ObjBox::isReadyToDestroy()
{
	return currHP <= 0.0f && onAnimEnded(1);
}
