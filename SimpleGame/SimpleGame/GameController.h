#pragma once

class GameController
{
protected:
	bool keyW{}, keyA{}, keyS{}, keyD{};
protected:
	GameController();
	virtual ~GameController();
public:
	void keyDownInput(unsigned char key, int x, int y);
	void keyUpInput(unsigned char key, int x, int y);
};

