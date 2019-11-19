#pragma once

#include "GameObj.h"

class Bullet : public GameObj
{
private:
	class GameController* gameCon{};
public:
	Bullet(Obj name, const Vector& pos);
	Bullet(Obj name, const Vector& pos, const Vector& vel);
	virtual ~Bullet() override;

	virtual void init(Obj name, const Vector& pos) override;
	void init(Obj name, const Vector& pos, const Vector& vel);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};