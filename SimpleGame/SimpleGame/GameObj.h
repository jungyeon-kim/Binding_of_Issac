#pragma once

class Renderer;

class GameObj
{
private:
	std::unique_ptr<Renderer> renderer{};
protected:
	float objMass{};
	Vector objPos{}, objVel{}, objAcc{}, objVol{}, objForce{};
	Color objCol{};

	float forceAmount{};
public:
	GameObj();
	virtual ~GameObj();

	virtual void update(float eTime);
	virtual void render();
	void addForce(float eTime);

	float getMass() const;
	const Vector& getForce() const;
	const Vector& getPos() const;
	const Vector& getVel() const;
	const Vector& getAcc() const;
	const Vector& getVol() const;
	const Color& getCol() const;
	void setMass(float mass);
	void setForce(const Vector& force);
	void setPos(const Vector& pos);
	void setVel(const Vector& vel);
	void setAcc(const Vector& acc);
	void setVol(const Vector& vol);
	void setCol(const Color& color);

	float getForceAmount() const;
	void setForceAmount(float amount);
};

