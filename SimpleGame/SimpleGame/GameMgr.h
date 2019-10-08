#pragma once

struct Vector;
struct Color;

class Renderer;
class GameObj;

class GameMgr	// Singleton
{
private:
	static constexpr int MAX_OBJECT{ 3 };
	int currTime{}, prevTime{}, elapsedTime{};
	static GameMgr* instance;
	std::unique_ptr<Renderer> renderer{};
	std::list<std::unique_ptr<GameObj>> obj{};
private:
	GameMgr();
	~GameMgr();
public:
	static GameMgr* getInstance();
	void update(float eTime);
	void renderScene();
	void addObject(const Vector& pos, const Vector& vol, const Color& col);
	void deleteObject();
	void testKeyInput(unsigned char c);

	int getElapsedTime();
};

