#include "stdafx.h"
#include "GameObj.h"

GameObj::GameObj() : 
	objWt{ -1 }, objPos{ -1, -1, -1 },
	objVel{ -1, -1, -1 }, objAcc{ -1, -1, -1 },
	objVol{ -1, -1, -1 }, objCol{ -1, -1, -1, -1 }
{
}

GameObj::~GameObj()
{
}

void GameObj::update(float eTime)
{
	objPos.x += objVel.x * eTime * meter();
	objPos.y += objVel.y * eTime * meter();
	objPos.z += objVel.z * eTime * meter();
}

void GameObj::addForce(float x, float y, float z, float eTime)
{
	objAcc.x = x / objWt;
	objAcc.y = y / objWt;
	objAcc.z = z / objWt;
	
	objVel.x += objAcc.x * eTime;
	objVel.y += objAcc.y * eTime;
	objVel.z += objAcc.z * eTime;
}

float GameObj::getWt() const
{
	return objWt;
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

void GameObj::setWt(float wt)
{
	objWt = wt;
}

void GameObj::setPos(const Vector& pos)
{
	objPos.x = pos.x * meter();
	objPos.y = pos.y * meter();
	objPos.z = pos.z * meter();
}

void GameObj::setVel(const Vector& vel)
{
	objVel.x = vel.x;
	objVel.y = vel.y;
	objVel.z = vel.z;
}

void GameObj::setAcc(const Vector& acc)
{
	objAcc.x = acc.x;
	objAcc.y = acc.y;
	objAcc.z = acc.z;
}

void GameObj::setVol(const Vector& vol)
{
	objVol.x = vol.x * meter();
	objVol.y = vol.y * meter();
	objVol.z = vol.z * meter();
}

void GameObj::setCol(const Color& col)
{
	objCol.r = col.r;
	objCol.g = col.g;
	objCol.b = col.b;
	objCol.a = col.a;
}
