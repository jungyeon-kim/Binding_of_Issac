#include "stdafx.h"
#include "BlockBox.h"
#include "Renderer.h"
#include "Physics.h"


BlockBox::BlockBox(const Vector& pos)
{
	init(pos);
}

BlockBox::~BlockBox()
{
}

void BlockBox::init(const Vector& pos)
{
	forceAmount;
	fricCoef = 9999.0f;
	objForce;
	objPos = pos;
	objVel;
	objAcc;
	objVol = { meter(), meter(), meter() };
	objCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	objMass = 9999.0f;
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
	renderer->DrawSolidRect(objPos, objVol, objCol);
}

void BlockBox::addForce()
{
}
