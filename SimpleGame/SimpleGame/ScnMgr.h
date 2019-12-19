#pragma once

class ScnMgr final
{
private:
	enum class SCENE {
		TITLE, IN_GAME, ENDING
	};
private:
	static constexpr int column{ wndSizeY / 100 }, row{ wndSizeX / 100 };

	int currTime{}, prevTime{}, elapsedTime{};
	int levelNameIdx{};
	bool onChangeLevel{};

	int sceneCnt{};
	SCENE scene{};

	std::string levelTile[column][row]{};
	std::ifstream tileData{};
	std::vector<int> texID{};

	static ScnMgr* instance;
	std::shared_ptr<class Renderer> renderer{};
private:
	ScnMgr();
	~ScnMgr();
public:
	static ScnMgr* getInstance();

	void init();
	void update(float eTime);
	void render();

	bool readTileData(const std::string& fileName);
	void tryChangeLevel();
	void setLevel(const std::string& fileName);

	void keyDownInput(unsigned char key, int x, int y) const;
	void keyUpInput(unsigned char key, int x, int y) const;
	void specialKeyDownInput(int key, int x, int y) const;
	void specialKeyUpInput(int key, int x, int y) const;

	int getElapsedTime();
};