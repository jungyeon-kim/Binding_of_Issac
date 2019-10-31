#pragma once

#include "GameObj.h"

class GameController;

class Bullet : public GameObj
{
private:
	GameController* gameCon{};
public:
	Bullet(const Vector& pos);
	Bullet(const Vector& pos, const Vector& vel);
	virtual ~Bullet();

	virtual void init(const Vector& pos) override;
	void init(const Vector& pos, const Vector& vel);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};

