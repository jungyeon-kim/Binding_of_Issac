#pragma once

class Renderer;
class GameObj;

class GameMgr	// Singleton
{
private:
	static constexpr int MAX_OBJECT{ 3 };
	static constexpr int HERO_OBJECT{ 0 };
	int currTime{}, prevTime{}, elapsedTime{};
	bool keyW{}, keyA{}, keyS{}, keyD{};
	static GameMgr* instance;
	std::unique_ptr<Renderer> renderer{};
	std::vector<std::unique_ptr<GameObj>> obj{};
private:
	GameMgr();
	~GameMgr();
public:
	static GameMgr* getInstance();
	void update(float eTime);
	void renderScene();
	void addObject(const Vector& pos, const Vector& vol, const Color& col);
	void deleteObject();
	void keyDownInput(unsigned char key, int x, int y);
	void keyUpInput(unsigned char key, int x, int y);

	void testKeyInput(unsigned char c);

	int getElapsedTime();
};

