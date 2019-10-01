#pragma once

struct ObjLocation;
struct ObjSize;
struct ObjColor;

class Renderer;
class GameObj;

class GameMgr	// Singleton
{
private:
	static constexpr int MAX_OBJECT{ 10 };
	static GameMgr* instance;
	std::unique_ptr<Renderer> renderer{};
	std::unique_ptr<GameObj> obj[MAX_OBJECT]{};
private:
	GameMgr();
	~GameMgr();
public:
	static GameMgr* getInstance();
	void renderScene();
	int addObject(const ObjLocation& loc, const ObjSize& size, const ObjColor& color);
	void deleteObject(int idx);
	void testKeyInput(unsigned char c);
};

