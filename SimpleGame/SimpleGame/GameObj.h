#pragma once

class GameObj
{
private:
	float objWt{};
	Vector objPos{}, objVel{}, objAcc{}, objVol{};
	Color objCol{};
public:
	GameObj();
	~GameObj();

	void update(float eTime);

	float getWt() const;
	Vector getPos() const;
	Vector getVel() const;
	Vector getAcc() const;
	Vector getVol() const;
	Color getCol() const;
	void setWt(float wt);
	void setPos(const Vector& pos);
	void setVel(const Vector& vel);
	void setAcc(const Vector& acc);
	void setVol(const Vector& vol);
	void setCol(const Color& color);
};

