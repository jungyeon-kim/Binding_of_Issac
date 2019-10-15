#pragma once

#include "GameController.h"

class GameController;
class Renderer;
class Player;

// Singleton
class GameMgr final
{
private:
	static constexpr int MAX_OBJECT{ 3 };
	int currTime{}, prevTime{}, elapsedTime{};

	static GameMgr* instance;
	GameController* gameCon;
	std::unique_ptr<Renderer> renderer{};
	std::unique_ptr<Player> player{};
	std::vector<std::unique_ptr<Player>> test{};
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

