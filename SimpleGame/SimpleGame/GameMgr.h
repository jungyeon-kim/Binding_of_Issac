#pragma once

class Renderer;
class GameController;
class Player;
class Bullet;

//	map<string, T>���� GameObj�� ����ϴ� ������Ʈ�� �����ϵ��� �ٲܰ�
/*
	SimpleGame->KeyInput ~ gameMgr->KeyInput ~ gameCon->KeyInput ~ gameCon-> �Ѿ� �� ����, �߻� �Һ��� T or F
	~ gameMgr->update->if(gameCon->shoot) addObject ~ bullet->update->gameCon->dir������ �̵�
*/
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
public:
	static GameMgr* getInstance();

	void init();
	void update(float eTime);
	void render();
	void addObject(const Vector& pos, const Vector& vol, const Color& col);
	void deleteObject();

	void keyDownInput(unsigned char key, int x, int y);
	void keyUpInput(unsigned char key, int x, int y);
	void specialKeyDownInput(int key, int x, int y);
	void specialKeyUpInput(int key, int x, int y);

	int getElapsedTime();
};

