#pragma once

class GameObj;

class Physics
{
private:
	float forceAmount{};	// »˚¿« æÁ
	float scalarVec{};		// ∫§≈Õ¿« ≈©±‚(±Ê¿Ã)
	Vector unitVec{};		// ¥‹¿ß∫§≈Õ
	Vector fricForce{};		// ∏∂¬˚∑¬
	Vector vel{}, acc{};

	bool bbOverlapTest(const GameObj& A, const GameObj& B);
public:
	Physics();
	~Physics();

	float getScalar(const Vector& vec);
	const Vector& getAcc(Vector acc, Vector force, float mass);
	const Vector& getVel(Vector vel, Vector acc, float eTime);
	const Vector& getPos(Vector pos, Vector vel, Vector acc, float eTime);
	const Vector& getVelByFric(Vector vel, float mass, float fricCoef, float eTime);

	bool isCollidable(Obj lName, Obj rName);
	bool isOverlap(Obj lName, Obj rName, const GameObj& A, const GameObj& B, int collisionType = 0);
	void processCollision(GameObj& A, GameObj& B);
};
