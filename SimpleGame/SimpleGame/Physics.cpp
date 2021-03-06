#include "stdafx.h"
#include "Physics.h"
#include "GameObj.h"

Physics::Physics()
{
}

Physics::~Physics()
{
}

void Physics::update(GameObj& obj, float eTime, float maxVel)
{
	obj.setForce({ 0.0f, 0.0f, 0.0f });
	obj.addForce();

	// Update Physics
	obj.setAcc(calcAcc(obj.getAcc(), obj.getForce(), obj.getMass()));
	obj.setVel(calcVel(obj.getVel(), obj.getAcc(), eTime, maxVel));
	obj.setVel(calcVelByFric(obj.getVel(), obj.getMass(), obj.getFricCoef(), eTime));
	obj.setPos(calcPos(obj.getPos(), obj.getVel(), obj.getAcc(), eTime));
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
const Vector& Physics::calcAcc(Vector acc, Vector force, float mass)
{
	acc = force / mass;

	return acc;
}

// vel = vel + acc * eTime
const Vector& Physics::calcVel(Vector vel, Vector acc, float eTime, float maxVel)
{
	if (getScalar(vel) < maxVel) vel = vel + acc * eTime;

	return vel;
}

// pos = pos + vel * eTime + 1 / 2 * acc * eTime ^ 2
const Vector& Physics::calcPos(Vector pos, Vector vel, Vector acc, float eTime)
{
	pos = pos + (vel * eTime + acc * pow(eTime, 2) * 1 / 2) * meter();

	return pos;
}

// calculate friction force & apply to velocity
const Vector& Physics::calcVelByFric(Vector vel, float mass, float fricCoef, float eTime)
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

bool Physics::isCollidable(OBJ lName, OBJ rName)
{
	if (lName == rName) return false;
	else if (lName == OBJ::PLAYER_BULLET && rName == OBJ::PLAYER) return false;
	else if (lName == OBJ::SKY_ENEMY && rName == OBJ::GROUND_ENEMY) return false;
	else if (lName == OBJ::ENEMY_BULLET && rName == OBJ::GROUND_ENEMY) return false;
	else if (lName == OBJ::ENEMY_BULLET && rName == OBJ::SKY_ENEMY) return false;
	else if (lName == OBJ::SKY_ENEMY && rName == OBJ::OBJ_BOX) return false;
	else if (lName == OBJ::ENEMY_BULLET && rName == OBJ::PLAYER_BULLET) return false;
	
	return true;
}

bool Physics::isOverlap(OBJ lName, OBJ rName, const GameObj& A, const GameObj& B)
{
	if (isCollidable(lName, rName)) return bbOverlapTest(A, B);
	return false;
}

void Physics::processCollision(GameObj& A, GameObj& B)
{
	if (A.getEnableCollision() && B.getEnableCollision())
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
}
