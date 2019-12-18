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

	void update(GameObj& obj, float eTime, float maxVel = 10.0f);

	const Vector& calcAcc(Vector acc, Vector force, float mass);
	const Vector& calcVel(Vector vel, Vector acc, float eTime, float maxVel);
	const Vector& calcPos(Vector pos, Vector vel, Vector acc, float eTime);
	const Vector& calcVelByFric(Vector vel, float mass, float fricCoef, float eTime);

	float getScalar(const Vector& vec);
	Vector getUnit(const Vector& vec);

	bool isCollidable(OBJ lName, OBJ rName);
	bool isOverlap(OBJ lName, OBJ rName, const GameObj& A, const GameObj& B);
	void processCollision(GameObj& A, GameObj& B);
};
