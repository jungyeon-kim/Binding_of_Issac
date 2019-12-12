#pragma once

#include "GameObj.h"

class BlockBox : public GameObj
{
private:
	std::uniform_int_distribution<> uid{ 0, 100 };
public:
	BlockBox(const Vector& pos);
	BlockBox(Tex texID, const Vector& pos);
	virtual ~BlockBox();

	virtual void init(const Vector & pos) override;
	void init(Tex texID, const Vector& pos);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;
};

