#pragma once

#include "GameActor.h"

class Fly : public GameActor
{
private:
	Vector moveDir{};
	std::uniform_int_distribution<> uidAnimX{};
public:
	Fly(const Vector& pos);
	~Fly();

	virtual void init(const Vector& pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;
};

