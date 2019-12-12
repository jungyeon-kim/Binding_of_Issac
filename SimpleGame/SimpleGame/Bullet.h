#pragma once

#include "GameActor.h"

class Bullet : public GameActor
{
public:
	Bullet(const Vector& pos);
	Bullet(Tex texID, const Vector& pos);
	virtual ~Bullet() override;

	virtual void init(const Vector& pos) override;
	void init(Tex texID, const Vector& pos);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;
};