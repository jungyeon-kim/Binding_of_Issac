#pragma once

#include "GameActor.h"

class Polyc : public GameActor
{
private:
	int bulletCoolTime{};
public:
	Polyc(const Vector& pos);
	~Polyc();

	virtual void init(const Vector & pos) override;
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;
};

