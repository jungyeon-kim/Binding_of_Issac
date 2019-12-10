#include "stdafx.h"
#include "GameActor.h"
#include "GameController.h"
#include "Renderer.h"
#include "Physics.h"

using namespace std;

GameActor::GameActor()
{
	init();
}

GameActor::~GameActor()
{
}

void GameActor::init()
{
	// must initialize it because of onAnimEnded().
	for (int i = 0; i < MAX_ANIM_NUM; ++i)
	{
		finalAnimX[i] = -1;
		finalAnimY[i] = -1;
	}
}

void GameActor::update(float eTime)
{
	GameObj::update(eTime);
}

void GameActor::render()
{
	GameObj::render();

	if (gameCon->isRunDebugMode())
	{
		renderer->DrawSolidRectGauge(objPos, { 0.0f, objVol.y / 1.5f, 0.0f },
			{ objVol.x, meter(0.15f), 0.0f }, { 0.8f, 0.8f, 0.8f, 0.3f }, 100.0f);
		renderer->DrawSolidRectGauge(objPos, { 0.0f, objVol.y / 1.5f, 0.0f },
			{ objVol.x, meter(0.15f), 0.0f }, { 1.0f, 0.0f, 0.0f, 0.3f }, (currHP / maxHP) * 100.0f);
	}
}

void GameActor::takeDamage(float damage, const GameActor& attacker)
{
	if (attacker.getEnableCollision()) currHP -= damage;
}

void GameActor::doAnimCycle(int cyclePeriod, int nextXPeriod, int nextYPeriod, int idx)
{
	if (idx < 10)
	{
		finalAnimX[idx] = nextXPeriod - 1;
		finalAnimY[idx] = nextYPeriod - 1;

		if (!(++animCycle[idx] % cyclePeriod))
		{
			++nextAnimX[idx] %= nextXPeriod;
			if (!nextAnimX[idx] && nextYPeriod) ++nextAnimY[idx] %= nextYPeriod;
			animCycle[idx] = 0;
		}
	}
	else
		cout << "doAnimCycle:: Maximum animation index is 9. \n";
}

bool GameActor::onAnimEnded(int idx)
{
	return nextAnimX[idx] == finalAnimX[idx] && nextAnimY[idx] == finalAnimY[idx];
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
