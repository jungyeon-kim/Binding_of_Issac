#pragma once

class Renderer;

class GameMgr
{
private:
	Renderer* renderer{};
public:
	GameMgr();
	~GameMgr();

	void renderScene();
};

