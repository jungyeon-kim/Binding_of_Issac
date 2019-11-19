#pragma once

#include "GameObj.h"

class Bullet : public GameObj
{
private:
	class GameController* gameCon{};
public:
	Bullet(Tex name, const Vector& pos);
	Bullet(Tex name, const Vector& pos, const Vector& vel);
	virtual ~Bullet() override;

	virtual void init(Tex name, const Vector& pos) override;
	void init(Tex name, const Vector& pos, const Vector& vel);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};