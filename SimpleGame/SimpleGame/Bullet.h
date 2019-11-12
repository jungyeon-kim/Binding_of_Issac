#pragma once

#include "GameObj.h"

class Bullet : public GameObj
{
private:
	static int TEX_ID;

	class GameController* gameCon{};
public:
	Bullet(const Vector& pos);
	Bullet(const Vector& pos, const Vector& vel);
	virtual ~Bullet();

	virtual void init(const Vector& pos) override;
	void init(const Vector& pos, const Vector& vel);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
};

