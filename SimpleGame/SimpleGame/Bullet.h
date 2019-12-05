#pragma once

#include "GameActor.h"

class Bullet : public GameActor
{
private:
	class GameController* gameCon{};
public:
	Bullet(const Vector& pos);
	Bullet(const Vector& pos, const Vector& vel);
	virtual ~Bullet() override;

	virtual void init(const Vector& pos) override;
	void init(const Vector& pos, const Vector& vel);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};