#pragma once

#include "./Dependencies/IrrKlang.h"
#pragma comment(lib, "irrKlang.lib") 

using namespace irrklang;

class SoundMgr
{
private:
	using SoundContainer = std::unique_ptr<std::map<SOUND, int>>;
private:
	static SoundMgr* instance;
	ISoundEngine* m_engine = NULL;
	std::map<int, ISound*> m_bgSoundList;
	std::map<int, ISoundSource*> m_shortSoundList;
	SoundContainer sound{};
private:
	SoundMgr();
	~SoundMgr();
public:
	static SoundMgr* getInstance();

	void init();

	int CreateBGSound(char* filePath);
	void DeleteBGSound(int index);
	void PlayBGSound(int index, bool bLoop, float volume);
	void StopBGSound(int index);

	int CreateShortSound(char* filePath);
	void DeleteShortSound(int index);
	void PlayShortSound(int index, bool bLoop, float volume);		

	int getSound(SOUND name) const;
};

