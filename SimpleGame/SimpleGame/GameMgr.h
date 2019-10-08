#pragma once

struct Vector;
struct Color;

class Renderer;
class GameObj;

class GameMgr	// Singleton
{
private:
	static constexpr int MAX_OBJECT{ 3 };
	static GameMgr* instance;
	std::unique_ptr<Renderer> renderer{};
	std::unique_ptr<GameObj> obj[MAX_OBJECT]{};
private:
	GameMgr();
	~GameMgr();
public:
	static GameMgr* getInstance();
	void update(float eTime);
	void renderScene();
	int addObject(const Vector& pos, const Vector& vol, const Color& col);
	void deleteObject(int idx);
	void testKeyInput(unsigned char c);
};

