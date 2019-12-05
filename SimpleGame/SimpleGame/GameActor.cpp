#include "stdafx.h"
#include "GameActor.h"
#include "Physics.h"

GameActor::GameActor()
{
}

GameActor::~GameActor()
{
}

void GameActor::takeDamage(float damage)
{
	currHP -= damage;
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
