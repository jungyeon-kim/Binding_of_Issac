#include "stdafx.h"
#include "GameObj.h"
#include "Renderer.h"

GameObj::GameObj()
{
}

GameObj::~GameObj()
{
}

float GameObj::getForceAmount() const
{
	return forceAmount;
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

void GameObj::setForceAmount(float amount)
{
	forceAmount = amount;
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