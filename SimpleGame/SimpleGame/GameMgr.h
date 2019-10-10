#pragma once

#include "GameController.h"

class Renderer;
class GameObj;

// Singleton
class GameMgr final : public GameController
{
private:
	static constexpr int MAX_OBJECT{ 3 };
	static constexpr int HERO_OBJECT{ 0 };
	int currTime{}, prevTime{}, elapsedTime{};

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

	int getElapsedTime();
};

