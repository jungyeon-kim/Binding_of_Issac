#pragma once

#include "GameActor.h"

class Player : public GameActor
{
private:
	enum class Skill { SHOOT };
	using CoolTimeContainer = std::unique_ptr<std::map<Skill, float>>;
private:
	static constexpr float MAX_VEL{ 5.0f };

	int destroyCnt{};
	int canDamagedCycle{};
	bool canDamaged{};

	CoolTimeContainer maxCoolTime{};
	CoolTimeContainer currCoolTime{};
public:
	Player(const Vector& pos);
	virtual ~Player() override;

	virtual void init(const Vector& pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual void takeDamage(float damage, OBJ attackerType, const GameActor& attacker) override;
	virtual bool isReadyToDestroy() override;

	void createBullet();

	bool isEndCoolTime(Skill name) const;
	void resetCoolTime(Skill name);
	void setCoolTime();
};