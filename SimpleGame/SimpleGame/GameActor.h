#pragma once

#include "GameObj.h"

class GameActor abstract : public GameObj
{
protected:
	static constexpr int MAX_ANIM_NUM{ 10 };

	float maxHP{};
	float currHP{};
	float damage{};

	std::array<int, MAX_ANIM_NUM> animCycle{};
	std::array<int, MAX_ANIM_NUM> currAnimX{}, currAnimY{};
	std::array<int, MAX_ANIM_NUM> finalAnimX{}, finalAnimY{};
public:
	GameActor();
	virtual ~GameActor();

	void init();
	virtual void init(const Vector& pos) override = 0;
	virtual void update(float eTime) override = 0;
	virtual void render() override = 0;
	virtual void addForce() override = 0;
	virtual bool isReadyToDestroy() override = 0;
	virtual void takeDamage(float damage, Obj attackerType, const GameActor& attacker);
	// Maximum animation index is 9.
	virtual void doAnimCycle(int cyclePeriod, int animXPeriod, int animYPeriod, int idx);
	virtual bool onAnimEnded(int idx);

	float getMaxHP() const;
	float getCurrHP() const;
	float getDamage() const;

	void setMaxHP(float maxHP);
	void setCurrHP(float currHP);
	void setDamage(float damage);
};

