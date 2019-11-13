#pragma once

// Singleton
class ObjMgr final
{
private:
	template <typename T>
	using ObjContainer = std::unique_ptr<std::unordered_multimap<Obj, T>>;
private:
	static constexpr int MAX_OBJECT{ 5000 };

	static ObjMgr* instance;
	class GameController* gameCon{};
	std::unique_ptr<class Physics> physics{};
	ObjContainer<std::unique_ptr<class GameObj>> obj{};
private:
	ObjMgr();
	~ObjMgr();
	ObjMgr(const ObjMgr& rhs) = delete;
	ObjMgr& operator=(const ObjMgr& rhs) = delete;

	template <typename T>
	void addObject(Obj name, const Vector& pos);
	template <typename T>
	void addObject(Obj name, const Vector& pos, const Vector& vel);
	void deleteObject(Obj name);
	void garbageCollect();
public:
	static ObjMgr* getInstance();

	void init();
	void update(float eTime);
	void render();

	template <typename T>
	T* tryGetObj(Obj name) const;
};

#include "ObjMgr.hpp"