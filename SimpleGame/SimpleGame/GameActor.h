#pragma once

#include "GameObj.h"

class GameActor abstract : public GameObj
{
public:
	GameActor();
	virtual ~GameActor();

	virtual void init(const Vector & pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};

