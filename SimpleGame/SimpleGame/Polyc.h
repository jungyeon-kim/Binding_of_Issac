#pragma once

#include "GameActor.h"

class Polyc : public GameActor
{
private:
	int attackCycle{};
	bool canAttack{};
	bool doOnceFlag{};

	std::uniform_int_distribution<> uidAttackCycle{ 80, 300 };
public:
	Polyc(const Vector& pos);
	~Polyc();

	virtual void init(const Vector & pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;

	void createBullet(float first, float last, float plus,
		float fricCoef, float forceAmount, float damage);
};

