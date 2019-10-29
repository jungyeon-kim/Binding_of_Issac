#pragma once

class Renderer;
class Physics;

class GameObj abstract
{
protected:
	float forceAmount{};	// ÈûÀÇ ¾ç
	float fricCoef{};		// ¸¶Âû °è¼ö
	float objMass{};
	Vector objPos{}, objVel{}, objAcc{}, objVol{}, objForce{};
	Color objCol{};

	std::unique_ptr<Renderer> renderer{};
	std::unique_ptr<Physics> physics{};
public:
	GameObj();
	virtual ~GameObj();

	void init();
	virtual void init(const Vector& pos) = 0;
	virtual void update(float eTime) = 0;
	virtual void render() = 0;
	virtual void addForce() = 0;

	float getForceAmount() const;
	float getFricCoef() const;
	float getMass() const;
	const Vector& getForce() const;
	const Vector& getPos() const;
	const Vector& getVel() const;
	const Vector& getAcc() const;
	const Vector& getVol() const;
	const Color& getCol() const;

	void setForceAmount(float amount);
	void setFricCoef(float coef);
	void setMass(float mass);
	void setForce(const Vector& force);
	void setPos(const Vector& pos);
	void setVel(const Vector& vel);
	void setAcc(const Vector& acc);
	void setVol(const Vector& vol);
	void setCol(const Color& color);
};

