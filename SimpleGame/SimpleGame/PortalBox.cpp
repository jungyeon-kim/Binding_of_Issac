#include "stdafx.h"
#include "PortalBox.h"
#include "TexMgr.h"
#include "ScnMgr.h"
#include "Physics.h"
#include "Renderer.h"

using namespace std;

PortalBox::PortalBox(const Vector& pos)
{
	init(pos);
}

PortalBox::PortalBox(const Vector& pos, Tex texID)
{
	init(pos, texID);
}

PortalBox::~PortalBox()
{
}

void PortalBox::init(const Vector& pos)
{
	forceAmount;
	fricCoef = numeric_limits<float>::max();
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(0.7f), meter(0.7f), 0.0f };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 1.0f;

	debugCol = { 0.0f, 0.0f, 1.0f, 0.3f };
}

void PortalBox::init(const Vector& pos, Tex texID)
{
	init(pos);

	this->texID.emplace_back(texMgr->getTexture(texID));
}

void PortalBox::update(float eTime)
{
	GameObj::update(eTime);

	objForce = { 0.0f, 0.0f, 0.0f };
	addForce();

	// Update Physics
	objAcc = physics->getAcc(objAcc, objForce, objMass);
	objVel = physics->getVel(objVel, objAcc, eTime);
	objVel = physics->getVelByFric(objVel, objMass, fricCoef, eTime);
	objPos = physics->getPos(objPos, objVel, objAcc, eTime);
}

void PortalBox::render()
{
	GameObj::render();

	if (!texID.empty())
	{
		static const Vector& texVol{ objVol * 1.5f };
		renderer->DrawTextureRect(objPos, texVol, objCol, texID[0], false, 1.0f);
	}
}

void PortalBox::addForce()
{
}

bool PortalBox::isReadyToDestroy()
{
	return false;
}

void PortalBox::tryOpenDoor()
{
	scnMgr->tryChangeLevel();
}
