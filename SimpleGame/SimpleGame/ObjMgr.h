#pragma once

class ObjMgr final
{
private:
	template <typename T>
	using ObjContainer = std::unique_ptr<std::multimap<OBJ, T, std::greater<>>>;
private:
	static constexpr int MAX_OBJECT{ 5000 };

	int numOfEnemy{};

	static ObjMgr* instance;
	std::shared_ptr<class Physics> physics{};
	std::shared_ptr<class Renderer> renderer{};
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
	auto addObject(OBJ name, const Vector& pos);
	template <typename T>
	auto addObject(OBJ name, TEX texID, const Vector& pos);
	void deleteObject(OBJ name);
	void deleteAllObject();
	void deleteAllObjectByException(OBJ exceptedName);
	void garbageCollect();

	template <typename T>
	T* tryGetObj(OBJ name) const;
	int getNumOfEnemy() const;
	void resetNumOfEnemy();

	std::shared_ptr<class Physics> getPhysics() const;
	std::shared_ptr<class Renderer> getRenderer() const;
};

#include "ObjMgr.hpp"