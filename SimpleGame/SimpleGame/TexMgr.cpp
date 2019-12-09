#include "stdafx.h"
#include "TexMgr.h"
#include "Renderer.h"

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
	renderer = make_unique<Renderer>(wndSizeX, wndSizeY);
	texture = make_unique<map<Tex, int>>();

	texture->emplace(Tex::TEST, renderer->GenPngTexture("./Textures/TestImg.png"));
	texture->emplace(Tex::BACK_GROUND, renderer->GenPngTexture("./Textures/BACK_GROUND.png"));
	texture->emplace(Tex::FRONT_FRAME, renderer->GenPngTexture("./Textures/FRONT_FRAME.png"));

	texture->emplace(Tex::BLOCKBOX_ROCK, renderer->GenPngTexture("./Textures/BLOCKBOX_ROCK.png"));
	texture->emplace(Tex::PORTALBOX_DOOR, renderer->GenPngTexture("./Textures/PORTALBOX_DOOR.png"));

	texture->emplace(Tex::P_BLOOD1, renderer->GenPngTexture("./Textures/P_BLOOD1.png"));
	texture->emplace(Tex::P_BLOOD2, renderer->GenPngTexture("./Textures/P_BLOOD2.png"));
	texture->emplace(Tex::P_BLOOD3, renderer->GenPngTexture("./Textures/P_BLOOD3.png"));

	texture->emplace(Tex::PLAYER_HEAD, renderer->GenPngTexture("./Textures/PLAYER_HEAD.png"));
	texture->emplace(Tex::PLAYER_BODY, renderer->GenPngTexture("./Textures/PLAYER_BODY.png"));

	texture->emplace(Tex::PLAYER_BULLET, renderer->GenPngTexture("./Textures/PLAYER_BULLET.png"));
	texture->emplace(Tex::ENEMY_BULLET, renderer->GenPngTexture("./Textures/ENEMY_BULLET.png"));

	texture->emplace(Tex::ENEMY_MOMS_HAND, renderer->GenPngTexture("./Textures/ENEMY_MOMS_HAND.png"));
	texture->emplace(Tex::ENEMY_TENTACLE, renderer->GenPngTexture("./Textures/ENEMY_TENTACLE.png"));
}

int TexMgr::getTexture(Tex name) const
{
	return (*texture)[name];
}
