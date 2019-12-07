#pragma once

#include "GameActor.h"

class PlayerBullet : public GameActor
{
public:
	PlayerBullet(const Vector& pos);
	PlayerBullet(const Vector& pos, const Vector& vel);
	virtual ~PlayerBullet() override;

	virtual void init(const Vector& pos) override;
	void init(const Vector& pos, const Vector& vel);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;
};