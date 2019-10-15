#pragma once

#include "GameObj.h"

class Physics;

class Player : public GameObj
{
private:
	std::unique_ptr<Physics> physics{};
public:
	Player();
	virtual ~Player();

	virtual void init() override;
	virtual void update(float eTime) override;
	virtual void render() override;

	void addForce(float eTime);
};

