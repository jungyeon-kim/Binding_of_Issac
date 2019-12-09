#pragma once

#include "GameObj.h"

class PortalBox : public GameObj
{
private:
	bool isOpened{};
public:
	PortalBox(const Vector& pos);
	PortalBox(const Vector& pos, Tex texID);
	~PortalBox();

	virtual void init(const Vector& pos) override;
	void init(const Vector& pos, Tex texID);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;

	bool getIsOpend() const;
	void setIsOpend(bool boolean);
};

