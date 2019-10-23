#pragma once

#include "GameObj.h"

class GameController;

class Bullet : public GameObj
{
private:
	GameController* gameCon{};
public:
	Bullet();
	virtual ~Bullet();

	virtual void init() override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};

