#pragma once

#include "GameObj.h"

class GameController;

class Player : public GameObj
{
private:
	using CoolTimeContainer = std::unique_ptr<std::map<Skill, float>>;
private:
	static constexpr int MAX_SPEED{ 7 };
	static int TEX_ID;

	GameController* gameCon{};
	CoolTimeContainer coolTime{};
	CoolTimeContainer period{};
public:
	Player(const Vector& pos);
	virtual ~Player();

	virtual void init(const Vector& pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;

	bool isEndCoolTime(Skill name) const;
	void resetCoolTime(Skill name);

	void setCoolTime();
};

