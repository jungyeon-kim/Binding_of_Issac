#pragma once

// Singleton
class GameController final
{
private:
	Direction objShoot{};
	Direction objDir{};
	static GameController* instance;
private:
	GameController();
	~GameController();
public:
	static GameController* getInstance();

	void init();

	void keyDownInput(unsigned char key, int x, int y);
	void keyUpInput(unsigned char key, int x, int y);
	void specialKeyDownInput(int key, int x, int y);
	void specialKeyUpInput(int key, int x, int y);

	bool isShoot() const;

	const Direction& getShoot() const;
	const Direction& getDir() const;
};

