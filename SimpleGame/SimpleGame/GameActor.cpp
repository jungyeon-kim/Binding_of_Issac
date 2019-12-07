#include "stdafx.h"
#include "GameActor.h"
#include "Physics.h"

GameActor::GameActor()
{
}

GameActor::~GameActor()
{
}

void GameActor::update(float eTime)
{
	GameObj::update(eTime);
}

void GameActor::render()
{
	GameObj::render();
}

void GameActor::takeDamage(float damage)
{
	currHP -= damage;
}

void GameActor::doAnimCycle(int cyclePeriod, int nextXPeriod, int nextYPeriod)
{
	if (!(++animCycle % cyclePeriod))
	{
		++nextAnimX %= nextXPeriod;
		if (!nextAnimX && nextYPeriod) ++nextAnimY %= nextYPeriod;
		animCycle = 0;
	}
}

float GameActor::getMaxHP() const
{
	return maxHP;
}

float GameActor::getCurrHP() const
{
	return currHP;
}

float GameActor::getDamage() const
{
	return damage;
}

void GameActor::setMaxHP(float maxHP)
{
	this->maxHP = maxHP;
}

void GameActor::setCurrHP(float currHP)
{
	this->currHP = currHP;
}

void GameActor::setDamage(float damage)
{
	this->damage = damage;
}
