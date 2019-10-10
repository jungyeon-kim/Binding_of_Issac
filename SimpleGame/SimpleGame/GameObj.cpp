#include "stdafx.h"
#include "GameObj.h"
#include "Renderer.h"

using namespace std;

GameObj::GameObj()
{
	renderer = make_unique<Renderer>(wndSizeX, wndSizeY);
	if (!renderer->IsInitialized()) { cout << "Renderer could not be initialized.. \n"; }
}

GameObj::~GameObj()
{
}

void GameObj::update(float eTime)
{
	addForce(eTime);

	// pos = pos + vel * eTime
	objPos = { objPos.x + objVel.x * eTime * meter(), 
		objPos.y + objVel.y * eTime * meter(), 
		objPos.z + objVel.z * eTime * meter() };
}

void GameObj::render()
{
	renderer->DrawSolidRect(objPos.x, objPos.y, objPos.z, objVol.x,
		objCol.r, objCol.g, objCol.b, objCol.a);
}

void GameObj::addForce(float eTime)
{
	// acc = force / mass
	objAcc = { objForce.x / objMass, objForce.y / objMass, objForce.z / objMass };
	// vel = vel + acc * eTime
	objVel = { objVel.x + objAcc.x * eTime, objVel.y + objAcc.y * eTime, objVel.z + objAcc.z * eTime };
}

float GameObj::getMass() const
{
	return objMass;
}

const Vector& GameObj::getForce() const
{
	return objForce;
}

const Vector& GameObj::getPos() const
{
	return objPos;
}

const Vector& GameObj::getVel() const
{
	return objVel;
}

const Vector& GameObj::getAcc() const
{
	return objAcc;
}

const Vector& GameObj::getVol() const
{
	return objVol;
}

const Color& GameObj::getCol() const
{
	return objCol;
}

void GameObj::setMass(float mass)
{
	objMass = mass;
}

void GameObj::setForce(const Vector& force)
{
	objForce = force;
}

void GameObj::setPos(const Vector& pos)
{
	objPos = pos;
}

void GameObj::setVel(const Vector& vel)
{
	objVel = vel;
}

void GameObj::setAcc(const Vector& acc)
{
	objAcc = acc;
}

void GameObj::setVol(const Vector& vol)
{
	objVol = vol;
}

void GameObj::setCol(const Color& col)
{
	objCol = col;
}

float GameObj::getForceAmount() const
{
	return forceAmount;
}

void GameObj::setForceAmount(float amount)
{
	forceAmount = amount;
}
