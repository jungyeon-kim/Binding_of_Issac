#pragma once

// Singleton
class TexMgr final
{
private:
	using TextureContainer = std::unique_ptr<std::map<Tex, int>>;
private:
	static TexMgr* instance;
	std::unique_ptr<class Renderer> renderer{};
	TextureContainer texture{};
private:
	TexMgr();
	~TexMgr();
public:
	static TexMgr* getInstance();

	void init();

	int getTexture(Tex name) const;
};
