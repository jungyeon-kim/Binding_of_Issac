#include "stdafx.h"
#include "GameObj.h"
#include "Renderer.h"
#include "Physics.h"
#include "TexMgr.h"

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
	texture = TexMgr::getInstance();
	renderer = make_unique<Renderer>(wndSizeX, wndSizeY);
	physics = make_unique<Physics>();
}

void GameObj::takeDamage(float damage)
{
	currHP -= damage;
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

Vector GameObj::getForce() const
{
	return objForce;
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

float GameObj::getMaxHP() const
{
	return maxHP;
}

float GameObj::getCurrHP() const
{
	return currHP;
}

float GameObj::getDamage() const
{
	return damage;
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

void GameObj::setMaxHP(float maxHP)
{
	this->maxHP = maxHP;
}

void GameObj::setCurrHP(float currHP)
{
	this->currHP = currHP;
}

void GameObj::setDamage(float damage)
{
	this->damage = damage;
}
