#pragma once

#include "GameController.h"

class GameController;
class GameObj;
class Player;

// Singleton
class GameMgr final
{
private:
	static constexpr int MAX_OBJECT{ 3 };
	int currTime{}, prevTime{}, elapsedTime{};

	static GameMgr* instance;
	GameController* gameController;
	std::unique_ptr<Player> player{};
	std::vector<std::unique_ptr<GameObj>> obj{};
private:
	GameMgr();
	~GameMgr();
public:
	static GameMgr* getInstance();
	void update(float eTime);
	void render();
	void addObject(const Vector& pos, const Vector& vol, const Color& col);
	void deleteObject();

	GameController* getGameController() const;
	int getElapsedTime();
};

