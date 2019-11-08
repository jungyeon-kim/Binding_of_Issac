#pragma once

#include "GameObj.h"

class GameController;

class Player : public GameObj
{
private:
	using CoolTimeContainer = std::unique_ptr<std::map<std::string, float>>;
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

	bool isEndCoolTime(const std::string& name) const;
	void resetCoolTime(const std::string& name);

	void setCoolTime();
};

