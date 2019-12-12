#include "stdafx.h"
#include "BlockBox.h"
#include "TexMgr.h"
#include "Renderer.h"
#include "Physics.h"


BlockBox::BlockBox(const Vector& pos)
{
	init(pos);
}

BlockBox::BlockBox(Tex texID, const Vector& pos)
{
	init(texID, pos);
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
	objVol = { meter(0.95f), meter(0.95f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;

	debugCol = { 1.0f, 0.0f, 0.0f, 0.3f };
}

void BlockBox::init(Tex texID, const Vector& pos)
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

	physics->update(*this, eTime);
}

void BlockBox::render()
{
	GameObj::render();

	if (!texID.empty())
	{
		static const Vector& texVol{ objVol * 1.1f };
		renderer->DrawTextureRect(objPos, texVol, objCol, texID[0]);
	}
}

void BlockBox::addForce()
{
}

bool BlockBox::isReadyToDestroy()
{
	return false;
}
