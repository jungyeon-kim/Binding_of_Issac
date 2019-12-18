#pragma once

class ScnMgr final
{
private:
	static constexpr int column{ wndSizeY / 100 }, row{ wndSizeX / 100 };

	int levelNameIdx{};
	bool canChangeLevel{};

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
};

