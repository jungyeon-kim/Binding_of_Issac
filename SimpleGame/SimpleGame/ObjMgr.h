#pragma once

class ObjMgr final
{
private:
	template <typename T>
	using ObjContainer = std::unique_ptr<std::multimap<Obj, T, std::greater<>>>;
private:
	static constexpr int MAX_OBJECT{ 5000 };

	int numOfEnemy{};

	static ObjMgr* instance;
	std::unique_ptr<class Physics> physics{};
	ObjContainer<std::unique_ptr<class GameObj>> obj{};
private:
	ObjMgr();
	~ObjMgr();
public:
	static ObjMgr* getInstance();

	void init();
	void update(float eTime);
	void render();

	template <typename T>
	auto addObject(Obj name, const Vector& pos);
	template <typename T>
	auto addObject(Obj name, Tex texID, const Vector& pos);
	void deleteObject(Obj name);
	void deleteAllObject();
	void deleteAllObjectByException(Obj exceptedName);
	void garbageCollect();

	template <typename T>
	T* tryGetObj(Obj name) const;

	int getNumOfEnemy() const;
	void setNumOfEnemy(int num);
};

#include "ObjMgr.hpp"