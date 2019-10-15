#pragma once

class Physics
{
private:
	float forceAmount{};	// ���� ��
	float scalarVec{};		// ������ ũ��(����)
	Vector unitVec{};		// ��������
	Vector fricForce{};		// ������
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

