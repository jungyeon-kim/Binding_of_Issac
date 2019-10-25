#pragma once

class Renderer;
class GameController;
class GameObj;
class Player;
class Bullet;

//	map<string, T>으로 GameObj를 상속하는 오브젝트들 관리하도록 바꿀것
// Singleton
class GameMgr final
{
private:
	static constexpr int MAX_OBJECT{ 5000 };
	int currTime{}, prevTime{}, elapsedTime{};

	static GameMgr* instance;
	GameController* gameCon{};
	std::unique_ptr<Renderer> renderer{};
	std::unique_ptr<Player> player{};
	std::vector<std::unique_ptr<Bullet>> bullet{};
private:
	GameMgr();
	~GameMgr();

	void garbageCollect();
public:
	static GameMgr* getInstance();

	void init();
	void update(float eTime);
	void render();
	template <typename T>
	void addObject(std::string objName);
	void deleteObject();

	void keyDownInput(unsigned char key, int x, int y);
	void keyUpInput(unsigned char key, int x, int y);
	void specialKeyDownInput(int key, int x, int y);
	void specialKeyUpInput(int key, int x, int y);

	int getElapsedTime();
};

