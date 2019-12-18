#include "stdafx.h"
#include "TexMgr.h"
#include "ObjMgr.h"
#include "Renderer.h"

using namespace std;

TexMgr* TexMgr::instance{};

TexMgr::TexMgr()
{
	init();
}

TexMgr::~TexMgr()
{
}

TexMgr* TexMgr::getInstance()
{
	if (!instance) instance = new TexMgr{};
	return instance;
}

void TexMgr::init()
{
	renderer = objMgr->getRenderer();
	texture = make_unique<map<TEX, int>>();

	texture->emplace(TEX::TEST, renderer->GenPngTexture("./Textures/TestImg.png"));
	texture->emplace(TEX::SCENE_TITLE, renderer->GenPngTexture("./Textures/SCENE_TITLE.png"));
	texture->emplace(TEX::BACK_GROUND, renderer->GenPngTexture("./Textures/BACK_GROUND.png"));
	texture->emplace(TEX::FRONT_FRAME, renderer->GenPngTexture("./Textures/FRONT_FRAME.png"));
	texture->emplace(TEX::FRONT_HPBAR_FRAME, renderer->GenPngTexture("./Textures/FRONT_HPBAR_FRAME.png"));

	texture->emplace(TEX::OBJBOX_ROCK, renderer->GenPngTexture("./Textures/OBJBOX_ROCK.png"));
	texture->emplace(TEX::PORTALBOX_DOOR, renderer->GenPngTexture("./Textures/PORTALBOX_DOOR.png"));

	texture->emplace(TEX::P_BLOOD1, renderer->GenPngTexture("./Textures/P_BLOOD1.png"));
	texture->emplace(TEX::P_BLOOD2, renderer->GenPngTexture("./Textures/P_BLOOD2.png"));
	texture->emplace(TEX::P_BLOOD3, renderer->GenPngTexture("./Textures/P_BLOOD3.png"));
	texture->emplace(TEX::P_BLOOD4, renderer->GenPngTexture("./Textures/P_BLOOD4.png"));
	texture->emplace(TEX::P_BLOOD5, renderer->GenPngTexture("./Textures/P_BLOOD5.png"));
	texture->emplace(TEX::P_EXPLOSION1, renderer->GenPngTexture("./Textures/P_EXPLOSION1.png"));

	texture->emplace(TEX::PLAYER_HEAD, renderer->GenPngTexture("./Textures/PLAYER_HEAD.png"));
	texture->emplace(TEX::PLAYER_BODY, renderer->GenPngTexture("./Textures/PLAYER_BODY.png"));

	texture->emplace(TEX::PLAYER_BULLET, renderer->GenPngTexture("./Textures/PLAYER_BULLET.png"));
	texture->emplace(TEX::ENEMY_BULLET, renderer->GenPngTexture("./Textures/ENEMY_BULLET.png"));

	texture->emplace(TEX::ENEMY_MOMS_HAND, renderer->GenPngTexture("./Textures/ENEMY_MOMS_HAND.png"));
	texture->emplace(TEX::ENEMY_TENTACLE, renderer->GenPngTexture("./Textures/ENEMY_TENTACLE.png"));
	texture->emplace(TEX::ENEMY_POLYC, renderer->GenPngTexture("./Textures/ENEMY_POLYC.png"));
	texture->emplace(TEX::ENEMY_FLY, renderer->GenPngTexture("./Textures/ENEMY_FLY.png"));
	texture->emplace(TEX::ENEMY_JUDAS, renderer->GenPngTexture("./Textures/ENEMY_JUDAS.png"));
}

int TexMgr::getTexture(TEX name) const
{
	return (*texture)[name];
}
