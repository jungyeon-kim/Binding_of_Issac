#pragma once

// Singleton
class GameController final
{
private:
	Direction objDir{};
	static GameController* instance;
private:
	GameController();
	~GameController();
public:
	static GameController* getInstance();
	void keyDownInput(unsigned char key, int x, int y);
	void keyUpInput(unsigned char key, int x, int y);

	const Direction& getDir() const;
	void setDir(const Direction& dir);
};

