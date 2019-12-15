#pragma once

#include "GameActor.h"

class Tentacle : public GameActor
{
private:
	int spawnFlyCycle{};

	std::uniform_int_distribution<> uidAnimX{};
	std::uniform_int_distribution<> uidSpawnFlyCycle{ 250, 500 };
public:
	Tentacle(const Vector& pos);
	~Tentacle();

	virtual void init(const Vector & pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;

	void createFly();
};

