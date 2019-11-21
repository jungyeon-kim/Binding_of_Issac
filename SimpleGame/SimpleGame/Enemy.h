#pragma once

#include "GameObj.h"

class Enemy : public GameObj
{
public:
	Enemy(const Vector& pos);
	virtual ~Enemy() override;

	virtual void init(const Vector& pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};

