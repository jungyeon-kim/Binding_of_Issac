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

	texture->emplace(Tex::TEST, renderer->GenPngTexture("./textures/TestImg.png"));
	texture->emplace(Tex::ISAC_HEAD, renderer->GenPngTexture("./textures/ISAC_HEAD.png"));
	texture->emplace(Tex::ISAC_BODY, renderer->GenPngTexture("./textures/ISAC_BODY.png"));
	texture->emplace(Tex::BASIC_BULLET, renderer->GenPngTexture("./textures/BASIC_BULLET.png"));
}

int TexMgr::getTexture(Tex name) const
{
	return (*texture)[name];
}
