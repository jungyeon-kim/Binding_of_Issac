#pragma once

#include "GameObj.h"

class BlockBox : public GameObj
{
private:
	std::uniform_real_distribution<float> urdCol{ 0.0f, 1.0f };
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

