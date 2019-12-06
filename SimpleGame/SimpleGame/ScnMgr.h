#pragma once

// Singleton
class ScnMgr final
{
private:
	static constexpr int column{ wndSizeY / 100 }, row{ wndSizeX / 100 };

	int levelTile[column][row]{};
	bool onOtherLevel{};

	std::ifstream tileData{};
	std::vector<int> texID{};

	static ScnMgr* instance;
	std::unique_ptr<class Renderer> renderer{};
private:
	ScnMgr();
	~ScnMgr();
public:
	static ScnMgr* getInstance();

	void init();
	void update(float eTime);
	void render();

	bool readTileData(std::string fileName);
	void setLevel(std::string fileName);
};

