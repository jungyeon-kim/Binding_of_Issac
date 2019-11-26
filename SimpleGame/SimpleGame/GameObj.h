#pragma once

class GameObj abstract
{
protected:
	float forceAmount{};	// ÈûÀÇ ¾ç
	float fricCoef{};		// ¸¶Âû °è¼ö
	float objMass{};
	Vector objPos{}, objVel{}, objAcc{}, objVol{}, objForce{};
	Color objCol{};

	int texID{};
	float hp{};
	float damage{};

	class TexMgr* texture{};
	std::unique_ptr<class Renderer> renderer{};
	std::unique_ptr<class Physics> physics{};
public:
	GameObj();
	virtual ~GameObj();

	void init();
	virtual void init(const Vector& pos) = 0;
	virtual void update(float eTime) = 0;
	virtual void render() = 0;
	virtual void addForce() = 0;

	void takeDamage(float damage);

	float getForceAmount() const;
	float getFricCoef() const;
	float getMass() const;
	Vector getForce() const;
	Vector getPos() const;
	Vector getVel() const;
	Vector getAcc() const;
	Vector getVol() const;
	Color getCol() const;
	float getHP() const;
	float getDamage() const;

	void setForceAmount(float amount);
	void setFricCoef(float coef);
	void setMass(float mass);
	void setForce(const Vector& force);
	void setPos(const Vector& pos);
	void setVel(const Vector& vel);
	void setAcc(const Vector& acc);
	void setVol(const Vector& vol);
	void setCol(const Color& color);
	void setHP(float hp);
	void setDamage(float damage);
};