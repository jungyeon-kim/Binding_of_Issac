#include "stdafx.h"
#include "GameObj.h"
#include "Renderer.h"
#include "Physics.h"

using namespace std;

GameObj::GameObj()
{
	init();
}

GameObj::~GameObj()
{
}

void GameObj::init()
{
	renderer = make_unique<Renderer>(wndSizeX, wndSizeY);
	physics = make_unique<Physics>();
}

float GameObj::getForceAmount() const
{
	return forceAmount;
}

float GameObj::getFricCoef() const
{
	return fricCoef;
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

void GameObj::setFricCoef(float coef)
{
	fricCoef = coef;
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