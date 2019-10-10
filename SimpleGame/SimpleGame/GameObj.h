#pragma once

class GameObj
{
private:
	float objMass{};
	Vector objPos{}, objVel{}, objAcc{}, objVol{};
	Color objCol{};
public:
	GameObj();
	virtual ~GameObj();

	void update(float eTime);
	void addForce(float fX, float fY, float fZ, float eTime);

	float getMass() const;
	Vector getPos() const;
	Vector getVel() const;
	Vector getAcc() const;
	Vector getVol() const;
	Color getCol() const;
	void setMass(float mass);
	void setPos(const Vector& pos);
	void setVel(const Vector& vel);
	void setAcc(const Vector& acc);
	void setVol(const Vector& vol);
	void setCol(const Color& color);
};

