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
	using ObjContainer = std::unique_ptr<std::unordered_multimap<Obj, T>>;
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
	GameMgr(const GameMgr& rhs) = delete;
	GameMgr& operator=(const GameMgr& rhs) = delete;

	template <typename T>
	void addObject(Obj name, const Vector& pos);
	template <typename T>
	void addObject(Obj name, const Vector& pos, const Vector& vel);
	void deleteObject(Obj name);
	void garbageCollect();
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
	template <typename T>
	T* tryGetObj(Obj name) const;
};

#include "GameMgr.hpp"