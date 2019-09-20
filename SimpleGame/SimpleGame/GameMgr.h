#pragma once

struct ObjLocation;
struct ObjSize;
struct ObjColor;

class Renderer;
class GameObj;

class GameMgr
{
private:
	static constexpr int MAX_OBJECT{ 10 };
	Renderer* renderer{};
	GameObj* obj[MAX_OBJECT]{};
public:
	GameMgr();
	~GameMgr();

	void renderScene();
	int addObject(ObjLocation loc, ObjSize size, ObjColor color);
	void deleteObject(int idx);
	void testKeyInput(unsigned char c);
};

