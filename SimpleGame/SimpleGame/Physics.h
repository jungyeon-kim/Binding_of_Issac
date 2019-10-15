#pragma once

class Physics
{
private:
	float forceAmount{};	// 힘의 양
	float scalarVec{};		// 벡터의 크기(길이)
	Vector unitVec{};		// 단위벡터
	Vector fricForce{};		// 마찰력
	Vector vel{}, acc{};
public:
	Physics();
	~Physics();

	// acc = force / mass
	const Vector& calcAcc(Vector& acc, const Vector& force, float mass);
	// vel = vel + acc * eTime
	const Vector& calcVel(Vector& vel, const Vector& acc, float eTime);
	// pos = pos + vel * eTime
	const Vector& calcPos(Vector& pos, const Vector& vel, float eTime);
	// calculate friction force & apply to velocity
	const Vector& calcFric(Vector& vel, float mass, float fricCoef, float eTime);
};

