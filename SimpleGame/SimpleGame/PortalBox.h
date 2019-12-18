#pragma once

#include "GameObj.h"

class PortalBox : public GameObj
{
public:
	PortalBox(const Vector& pos);
	PortalBox(TEX texID, const Vector& pos);
	~PortalBox();

	virtual void init(const Vector& pos) override;
	void init(TEX texID, const Vector& pos);
	virtual void update(float eTime) override;
	virtual void render() override;
	virtual void addForce() override;
	virtual bool isReadyToDestroy() override;

	void tryOpenDoor();
};

