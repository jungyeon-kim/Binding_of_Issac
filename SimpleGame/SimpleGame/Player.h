#pragma once

#include "GameObj.h"

class GameController;

class Player : public GameObj
{
private:
	GameController* gameCon{};
public:
	Player(const Vector& pos);
	virtual ~Player();

	virtual void init(const Vector& pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};

