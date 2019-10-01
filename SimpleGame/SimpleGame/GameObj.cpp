#include "stdafx.h"
#include "GameObj.h"

GameObj::GameObj()
{
}

GameObj::~GameObj()
{
}

ObjPos GameObj::getPos() const
{
	return objPos;
}

ObjVel GameObj::getVel() const
{
	return objVel;
}

ObjAcc GameObj::getAcc() const
{
	return objAcc;
}

ObjVol GameObj::getVol() const
{
	return objVol;
}

ObjCol GameObj::getCol() const
{
	return objCol;
}

ObjWt GameObj::getWt() const
{
	return objWt;
}

void GameObj::setPos(const ObjPos& pos)
{
	objPos.x = pos.x;
	objPos.y = pos.y;
	objPos.z = pos.z;
}

void GameObj::setVel(const ObjVel& vel)
{
	objVel.x = vel.x;
	objVel.y = vel.y;
	objVel.z = vel.z;
}

void GameObj::setAcc(const ObjAcc& acc)
{
	objAcc.x = acc.x;
	objAcc.y = acc.y;
	objAcc.z = acc.z;
}

void GameObj::setVol(const ObjVol& vol)
{
	objVol.x = vol.x;
	objVol.y = vol.y;
	objVol.z = vol.z;
}

void GameObj::setCol(const ObjCol& col)
{
	objCol.r = col.r;
	objCol.g = col.g;
	objCol.b = col.b;
	objCol.a = col.a;
}

void GameObj::setWt(const ObjWt& wt)
{
	objWt.wt = wt.wt;
}
