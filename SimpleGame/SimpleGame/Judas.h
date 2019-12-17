#pragma once

#include "GameActor.h"

class Judas : public GameActor
{
private:
	int phase{};
	float currHPRatio{};

	std::array<int, 2> attackCycle{};
	std::uniform_int_distribution<> uidAttackCycle{ 100, 200 };
public:
	Judas(const Vector& pos);
	~Judas();

	virtual void init(const Vector& pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;

	void createBullet(float first, float last, float plus,
		float fricCoef, float forceAmount, float damage, 
		const Color& col = { 1.0f, 1.0f, 1.0f, 1.0f },
		const Vector& vol = { meter(0.25f), meter(0.25f), 0.0f });
	void createBullet(float value,
		float fricCoef, float forceAmount, float damage,
		const Color& col = { 1.0f, 1.0f, 1.0f, 1.0f },
		const Vector& vol = { meter(0.25f), meter(0.25f), 0.0f });
};

