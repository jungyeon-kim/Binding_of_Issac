#pragma once

#include "GameObj.h"

class Player : public GameObj
{
private:
	using CoolTimeContainer = std::unique_ptr<std::map<Skill, float>>;
private:
	static constexpr int MAX_SPEED{ 7 };

	class GameController* gameCon{};
	CoolTimeContainer coolTime{};
	CoolTimeContainer period{};
public:
	Player(Tex name, const Vector& pos);
	virtual ~Player() override;

	virtual void init(Tex name, const Vector& pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;

	bool isEndCoolTime(Skill name) const;
	void resetCoolTime(Skill name);

	void setCoolTime();
};