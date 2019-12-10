#pragma once

class GameObj abstract
{
protected:
	float forceAmount{};
	float fricCoef{};
	float objMass{};
	Vector objPos{}, objVel{}, objAcc{}, objVol{}, objForce{};
	Vector prevObjPos{};
	Color objCol{};
	
	Vector debugPos{};
	Color debugCol{};

	bool enableCollsion{};
	std::vector<int> texID{};
	std::random_device seed{};
	std::default_random_engine dre{ seed() };

	std::unique_ptr<class Physics> physics{};
public:
	GameObj();
	virtual ~GameObj();

	void init();
	virtual void init(const Vector& pos) = 0;
	virtual void update(float eTime) = 0;
	virtual void render() = 0;
	virtual void addForce() = 0;
	virtual bool isReadyToDestroy() = 0;

	bool getEnableCollision() const;
	void setEnableCollision(bool boolean);

	float getForceAmount() const;
	float getFricCoef() const;
	float getMass() const;
	Vector getForce() const;
	Vector getPos() const;
	Vector getVel() const;
	Vector getAcc() const;
	Vector getVol() const;
	Vector getPrevPos() const;
	Color getCol() const;

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