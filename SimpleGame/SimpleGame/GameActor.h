#pragma once

#include "GameObj.h"

class GameActor abstract : public GameObj
{
protected:
	float maxHP{};
	float currHP{};
	float damage{};
public:
	GameActor();
	virtual ~GameActor();

	virtual void init(const Vector & pos) override = 0;
	virtual void update(float eTime) override = 0;
	virtual void render() override = 0;
	virtual void addForce() override = 0;
	virtual void takeDamage(float damage);

	float getMaxHP() const;
	float getCurrHP() const;
	float getDamage() const;

	void setMaxHP(float maxHP);
	void setCurrHP(float currHP);
	void setDamage(float damage);
};

