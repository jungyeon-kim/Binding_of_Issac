#pragma once

#include "GameObj.h"

class GameController;

class Player : public GameObj
{
private:
	GameController* gameController{};
public:
	Player();
	virtual ~Player();

	virtual void update(float eTime) override;
};

