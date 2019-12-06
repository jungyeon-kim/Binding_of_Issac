#pragma once

// Singleton
class GameMgr final
{
private:
	int currTime{}, prevTime{}, elapsedTime{};

	static GameMgr* instance;
	class ObjMgr* objMgr{};
	class ScnMgr* scnMgr{};
	class GameController* gameCon{};
private:
	GameMgr();
	~GameMgr();
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