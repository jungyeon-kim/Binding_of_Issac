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

// acc = force / mass
const Vector& Physics::getAcc(Vector acc, Vector force, float mass)
{
	acc = force / mass;

	return acc;
}

// vel = vel + acc * eTime
const Vector& Physics::getVel(Vector vel, Vector acc, float eTime)
{
	vel = vel + acc * eTime;

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
	// normalize vector
	scalarVec = getScalar(vel);

	if (scalarVec > 0) 
	{
		//unitVec = vel / scalarVec;
		unitVec = { vel.x / scalarVec, vel.y / scalarVec };
		// calculate friction force
		forceAmount = mass * gravity;						// force = mass * acc
		fricForce = {										// fricForce = -unitVec * forceAmount * fricCoef
			-unitVec.x * forceAmount * fricCoef,
			-unitVec.y * forceAmount * fricCoef
		};
		// acceleration by fricForce
		acc = { fricForce.x / mass, fricForce.y / mass };	// acc = force / mass (음의 가속도)
		// update velocity
		this->vel = {										// vel = vel + acc * eTime (속도 감소)
			vel.x + acc.x * eTime,
			vel.y + acc.y * eTime
		};
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

bool Physics::isOverlap(const GameObj& A, const GameObj& B, int type)
{
	switch (type)
	{
	case 0:
		return bbOverlapTest(A, B);
		break;
	case 1:
		break;
	}
}

void Physics::processCollision(GameObj& A, GameObj& B)
{
	float aMass{ A.getMass() }, bMass{ B.getMass() };
	Vector aFinalVel{}, bFinalVel{};

	aFinalVel = A.getVel() * (aMass - bMass) / (aMass + bMass) + B.getVel() * 2.0f * bMass / (aMass + bMass);
	bFinalVel = B.getVel() * (bMass - aMass) / (bMass + aMass) + A.getVel() * 2.0f * aMass / (bMass + aMass);

	A.setVel(aFinalVel);
	B.setVel(bFinalVel);
}
