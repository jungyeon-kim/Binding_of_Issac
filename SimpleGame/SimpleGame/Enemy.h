#pragma once

#include "GameActor.h"

class Enemy : public GameActor
{
public:
	Enemy(const Vector& pos);
	virtual ~Enemy() override;

	virtual void init(const Vector& pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};

