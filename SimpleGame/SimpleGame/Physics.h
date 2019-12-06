#pragma once

class GameObj;

class Physics
{
private:
	Vector vel{};
private:
	bool bbOverlapTest(const GameObj& A, const GameObj& B);
public:
	Physics();
	~Physics();

	float getScalar(const Vector& vec);
	Vector getUnit(const Vector& vec);
	const Vector& getAcc(Vector acc, Vector force, float mass);
	const Vector& getVel(Vector vel, Vector acc, float eTime, float maxVel = 10.0f);
	const Vector& getPos(Vector pos, Vector vel, Vector acc, float eTime);
	const Vector& getVelByFric(Vector vel, float mass, float fricCoef, float eTime);

	bool isCollidable(Obj lName, Obj rName);
	bool isOverlap(Obj lName, Obj rName, const GameObj& A, const GameObj& B, int collisionType = 0);
	void processCollision(GameObj& A, GameObj& B);
};
