#pragma once

#include "GameObj.h"

class GameController;

class Player : public GameObj
{
private:
	GameController* gameCon{};
public:
	Player();
	virtual ~Player();

	virtual void init() override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void calcPhysics(float eTime) override;
};

