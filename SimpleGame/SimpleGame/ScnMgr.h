#pragma once

// Singleton
class ScnMgr final
{
private:
	static ScnMgr* instance;
	class ObjMgr* objMgr{};
private:
	ScnMgr();
	~ScnMgr();
public:
	static ScnMgr* getInstance();

	void init();
};

