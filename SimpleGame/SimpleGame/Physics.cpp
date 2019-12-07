#include "stdafx.h"
#include "Physics.h"
#include "GameObj.h"

Physics::Physics()
{
}

Physics::~Physics()
{
}

float Physics::getScalar(const Vector& vec)
{
	return sqrtf(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

Vector Physics::getUnit(const Vector& vec)
{
	float scalarVec{ getScalar(vec) };

	if (scalarVec) return { vec.x / scalarVec, vec.y / scalarVec, vec.z / scalarVec };
	else return { 0, 0, 0 };
}

// acc = force / mass
const Vector& Physics::getAcc(Vector acc, Vector force, float mass)
{
	acc = force / mass;

	return acc;
}

// vel = vel + acc * eTime
const Vector& Physics::getVel(Vector vel, Vector acc, float eTime, float maxVel)
{
	if (getScalar(vel) < maxVel) vel = vel + acc * eTime;

	return vel;
}

// pos = pos + vel * eTime + 1 / 2 * acc * eTime ^ 2
const Vector& Physics::getPos(Vector pos, Vector vel, Vector acc, float eTime)
{
	pos = pos + (vel * eTime + acc * pow(eTime, 2) * 1 / 2) * meter();

	return pos;
}

// calculate friction force & apply to velocity
const Vector& Physics::getVelByFric(Vector vel, float mass, float fricCoef, float eTime)
{
	float scalarVec{ getScalar(vel) };

	if (scalarVec) 
	{
		// normalize vector
		const Vector& unitVec{ vel / scalarVec };
		// calculate friction force
		float forceAmount{ mass * gravity };							// force = mass * acc
		const Vector& fricForce{ -unitVec * forceAmount * fricCoef };	// fricForce = -unitVec * forceAmount * fricCoef
		// acceleration by fricForce
		const Vector& acc{ fricForce / mass };							// acc = force / mass (음의 가속도)
		// update velocity
		this->vel = { vel + acc * eTime };								// vel = vel + acc * eTime (속도 감소)

		if (this->vel.x * vel.x < 0) vel.x = 0;
		else vel.x = this->vel.x;
		if (this->vel.y * vel.y < 0) vel.y = 0;
		else vel.y = this->vel.y;
	}

	return vel;
}

bool Physics::bbOverlapTest(const GameObj& A, const GameObj& B)
{
	Vector minA{}, maxA{};
	Vector minB{}, maxB{};

	minA = A.getPos() - A.getVol() / 2.0f;
	maxA = A.getPos() + A.getVol() / 2.0f;
	minB = B.getPos() - B.getVol() / 2.0f;
	maxB = B.getPos() + B.getVol() / 2.0f;

	if (minA > maxB || maxA < minB) return false;
	return true;
}

bool Physics::isCollidable(Obj lName, Obj rName)
{
	if (lName == rName)	return false;
	else if (lName == Obj::PLAYER_BULLET && rName == Obj::PLAYER) return false;
	else if (lName == Obj::ENEMY_BULLET && rName == Obj::ENEMY) return false;

	return true;
}

bool Physics::isOverlap(Obj lName, Obj rName, const GameObj& A, const GameObj& B, int collisionType)
{
	if (A.getEnableCollision() && B.getEnableCollision())
	{
		switch (collisionType)
		{
		case 0:
			if (isCollidable(lName, rName)) return bbOverlapTest(A, B);
			return false;
			break;
		default:
			return false;
			break;
		}
	}
	else 
		return false;
}

void Physics::processCollision(GameObj& A, GameObj& B)
{
	float aMass{ A.getMass() }, bMass{ B.getMass() };
	Vector aFinalVel{}, bFinalVel{};

	aFinalVel = A.getVel() * (aMass - bMass) / (aMass + bMass) + B.getVel() * 2.0f * bMass / (aMass + bMass);
	bFinalVel = B.getVel() * (bMass - aMass) / (bMass + aMass) + A.getVel() * 2.0f * aMass / (bMass + aMass);

	A.setPos(A.getPrevPos());
	B.setPos(B.getPrevPos());
	A.setVel(aFinalVel);
	B.setVel(bFinalVel);
}
