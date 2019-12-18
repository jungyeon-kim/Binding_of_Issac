#pragma once

#include "GameActor.h"

class ObjBox : public GameActor
{
private:
	std::uniform_real_distribution<float> urdCol{ 0.0f, 1.0f };
public:
	ObjBox(const Vector& pos);
	ObjBox(TEX texID, const Vector& pos);
	~ObjBox();

	virtual void init(const Vector& pos) override;
	void init(TEX texID, const Vector& pos);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual void takeDamage(float damage, OBJ attackerType, const GameActor& attacker) override;
	virtual bool isReadyToDestroy() override;
};

