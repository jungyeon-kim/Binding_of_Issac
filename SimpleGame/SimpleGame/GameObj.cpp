#include "stdafx.h"
#include "GameObj.h"

GameObj::GameObj()
{
}

GameObj::~GameObj()
{
}

ObjLocation GameObj::getLocation() const 
{ 
	return objLoc;
}

ObjSize GameObj::getSize() const 
{ 
	return objSize; 
}

ObjColor GameObj::getColor() const 
{ 
	return objColor; 
}

void GameObj::setLocation(ObjLocation loc)
{
	objLoc.posX = loc.posX;
	objLoc.posY = loc.posY;
	objLoc.posZ = loc.posZ;
}

void GameObj::setSize(ObjSize size)
{
	objSize.sizeX = size.sizeX;
	objSize.sizeY = size.sizeY;
	objSize.sizeZ = size.sizeZ;
}
void GameObj::setColor(ObjColor color)
{
	objColor.colorR = color.colorR;
	objColor.colorG = color.colorG;
	objColor.colorB = color.colorB;
	objColor.colorA = color.colorA;
}
