#pragma once

#include "GameObj.h"

class BlockBox : public GameObj
{
private:
	std::random_device seed{};
	std::default_random_engine dre{ seed() };
	std::uniform_int_distribution<> uid{ 0, 100 };
public:
	BlockBox(const Vector& pos);
	BlockBox(const Vector& pos, Tex texID);
	virtual ~BlockBox();

	virtual void init(const Vector & pos) override;
	void init(const Vector& pos, Tex texID);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;
};

