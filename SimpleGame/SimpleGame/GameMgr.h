#pragma once

class Renderer;
class Physics;
class GameController;
class GameObj;

// Singleton
class GameMgr final
{
private:
	template <typename T>
	using ObjContainer = std::unique_ptr<std::unordered_multimap<std::string, T>>;
private:
	static constexpr int MAX_OBJECT{ 5000 };
	int currTime{}, prevTime{}, elapsedTime{};

	static GameMgr* instance;
	GameController* gameCon{};
	std::unique_ptr<Renderer> renderer{};
	std::unique_ptr<Physics> physics{};
	ObjContainer<std::unique_ptr<GameObj>> obj{};
private:
	GameMgr();
	~GameMgr();

	template <typename T>
	void addObject(std::string objName);
	void deleteObject();
	void garbageCollect();
public:
	static GameMgr* getInstance();
	
	void init();
	void update(float eTime);
	void render();

	void keyDownInput(unsigned char key, int x, int y);
	void keyUpInput(unsigned char key, int x, int y);
	void specialKeyDownInput(int key, int x, int y);
	void specialKeyUpInput(int key, int x, int y);

	int getElapsedTime();
};

#include "GameMgr.hpp"