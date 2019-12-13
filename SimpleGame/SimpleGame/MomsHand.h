#pragma once

#include "GameActor.h"

class MomsHand : public GameActor
{
private:
	float dirX{}, dirY{};

	std::uniform_int_distribution<> uidDir{ -1, 1 };
public:
	MomsHand(const Vector& pos);
	~MomsHand();

	virtual void init(const Vector & pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;
};

