#pragma once

#include "GameActor.h"

class ObjBox : public GameActor
{
private:
	std::uniform_real_distribution<float> urdCol{ 0.0f, 1.0f };
public:
	ObjBox(const Vector& pos);
	ObjBox(Tex texID, const Vector& pos);
	~ObjBox();

	virtual void init(const Vector& pos) override;
	void init(Tex texID, const Vector& pos);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual void takeDamage(float damage, Obj attackerType, const GameActor& attacker) override;
	virtual bool isReadyToDestroy() override;
};

