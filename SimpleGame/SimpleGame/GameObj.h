#pragma once

struct ObjLocation { float posX{}, posY{}, posZ{}; };
struct ObjSize { float sizeX{}, sizeY{}, sizeZ{}; };
struct ObjColor { float colorR{}, colorG{}, colorB{}, colorA{}; };

class GameObj
{
private:
	ObjLocation objLoc{};
	ObjSize objSize{};
	ObjColor objColor{};
public:
	GameObj();
	~GameObj();

	ObjLocation getLocation() const;
	ObjSize getSize() const;
	ObjColor getColor() const;
	void setLocation(const ObjLocation& loc);
	void setSize(const ObjSize& size);
	void setColor(const ObjColor& color);
};

