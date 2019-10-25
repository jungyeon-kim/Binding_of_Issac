#pragma once

#include "GameObj.h"

class GameController;

class Bullet : public GameObj
{
private:
	GameController* gameCon{};
public:
	Bullet();
	Bullet(const Vector& pos, const Vector& vel);
	virtual ~Bullet();

	virtual void init() override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;

	void init(const Vector& pos, const Vector& vel);
};

