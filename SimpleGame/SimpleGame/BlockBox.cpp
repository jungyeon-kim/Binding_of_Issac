#include "stdafx.h"
#include "BlockBox.h"
#include "Physics.h"

using namespace std;

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

void BlockBox::update(float eTime)
{
	GameObj::update(eTime);

	physics->update(*this, eTime);
}

void BlockBox::render()
{
	GameObj::render();
}

void BlockBox::addForce()
{
}

bool BlockBox::isReadyToDestroy()
{
	return false;
}
