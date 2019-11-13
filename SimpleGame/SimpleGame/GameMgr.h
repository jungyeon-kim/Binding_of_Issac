#pragma once

// Singleton
class GameMgr final
{
private:
	int currTime{}, prevTime{}, elapsedTime{};

	static GameMgr* instance;
	class GameController* gameCon{};
	class ObjMgr* objMgr{};
private:
	GameMgr();
	~GameMgr();
	GameMgr(const GameMgr& rhs) = delete;
	GameMgr& operator=(const GameMgr& rhs) = delete;
public:
	static GameMgr* getInstance();
	
	void init();
	void update(float eTime);
	void render();

	void keyDownInput(unsigned char key, int x, int y) const;
	void keyUpInput(unsigned char key, int x, int y) const;
	void specialKeyDownInput(int key, int x, int y) const;
	void specialKeyUpInput(int key, int x, int y) const;

	int getElapsedTime();
};