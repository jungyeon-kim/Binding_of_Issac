#include "stdafx.h"
#include "Physics.h"

Physics::Physics()
{
}

Physics::~Physics()
{
}

float Physics::calcScalar(const Vector& vec)
{
	return sqrtf(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

const Vector& Physics::calcAcc(Vector& acc, const Vector& force, float mass)
{
	acc = {
		force.x / mass, 
		force.y / mass, 
		force.z / mass 
	};

	return acc;
}

const Vector& Physics::calcVel(Vector& vel, const Vector& acc, float eTime)
{
	vel = { 
		vel.x + acc.x * eTime, 
		vel.y + acc.y * eTime, 
		vel.z + acc.z * eTime 
	};

	return vel;
}

const Vector& Physics::calcPos(Vector& pos, const Vector& vel, float eTime)
{
	pos = { 
		pos.x + vel.x * eTime * meter(),
		pos.y + vel.y * eTime * meter(),
		pos.z + vel.z * eTime * meter()
	};

	return pos;
}

const Vector& Physics::calcFric(Vector& vel, float mass, float fricCoef, float eTime)
{
	// normalize vector
	scalarVec = calcScalar(vel);

	if (scalarVec > 0) 
	{
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
