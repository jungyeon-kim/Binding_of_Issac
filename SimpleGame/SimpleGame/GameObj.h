#pragma once

struct ObjPos { float x{ -1 }, y{ -1 }, z{ -1 }; };
struct ObjVel { float x{ -1 }, y{ -1 }, z{ -1 }; };
struct ObjAcc { float x{ -1 }, y{ -1 }, z{ -1 }; };
struct ObjVol { float x{ -1 }, y{ -1 }, z{ -1 }; };
struct ObjCol { float r{ -1 }, g{ -1 }, b{ -1 }, a{ -1 }; };
struct ObjWt { float wt{ -1 }; };

class GameObj
{
private:
	ObjPos objPos{};
	ObjVel objVel{};
	ObjAcc objAcc{};
	ObjVol objVol{};
	ObjCol objCol{};
	ObjWt objWt{};
public:
	GameObj();
	~GameObj();

	ObjPos getPos() const;
	ObjVel getVel() const;
	ObjAcc getAcc() const;
	ObjVol getVol() const;
	ObjCol getCol() const;
	ObjWt getWt() const;
	void setPos(const ObjPos& pos);
	void setVel(const ObjVel& vel);
	void setAcc(const ObjAcc& acc);
	void setVol(const ObjVol& vol);
	void setCol(const ObjCol& color);
	void setWt(const ObjWt& wt);
};

