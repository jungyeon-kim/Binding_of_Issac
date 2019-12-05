#pragma once

#include "GameObj.h"

class BlockBox : public GameObj
{
public:
	BlockBox(const Vector& pos);
	virtual ~BlockBox();

	virtual void init(const Vector & pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};

