#include "stdafx.h"
#include "GameObj.h"

GameObj::GameObj()
{
}

GameObj::~GameObj()
{
}

void GameObj::update(float eTime)
{
	objPos = { objPos.x + objVel.x * eTime * meter(), 
		objPos.y + objVel.y * eTime * meter(), 
		objPos.z + objVel.z * eTime * meter() };
}

void GameObj::addForce(float fX, float fY, float fZ, float eTime)
{
	// acc = force / mass
	objAcc = { fX / objMass, fY / objMass, fZ / objMass };
	// vel = vel + acc + eTime
	objVel = { objVel.x + objAcc.x * eTime, objVel.y + objAcc.y * eTime, objVel.z + objAcc.z * eTime };
}

float GameObj::getMass() const
{
	return objMass;
}

Vector GameObj::getPos() const
{
	return objPos;
}

Vector GameObj::getVel() const
{
	return objVel;
}

Vector GameObj::getAcc() const
{
	return objAcc;
}

Vector GameObj::getVol() const
{
	return objVol;
}

Color GameObj::getCol() const
{
	return objCol;
}

void GameObj::setMass(float mass)
{
	objMass = mass;
}

void GameObj::setPos(const Vector& pos)
{
	objPos = { pos.x * meter() , pos.y * meter(), pos.z * meter() };
}

void GameObj::setVel(const Vector& vel)
{
	objVel = { vel.x, vel.y, vel.z };
}

void GameObj::setAcc(const Vector& acc)
{
	objAcc = { acc.x, acc.y, acc.z };
}

void GameObj::setVol(const Vector& vol)
{
	objVol = { vol.x * meter(), vol.y * meter(), vol.z * meter() };
}

void GameObj::setCol(const Color& col)
{
	objCol = { col.r, col.g, col.b, col.a };
}
