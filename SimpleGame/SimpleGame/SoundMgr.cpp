#include "stdafx.h"
#include "SoundMgr.h"

#define MAX_SOUND 100

using namespace std;

SoundMgr* SoundMgr::instance{};

SoundMgr::SoundMgr()
{
	init();
}

SoundMgr::~SoundMgr()
{
	m_bgSoundList.clear();
	m_shortSoundList.clear();

	delete m_engine;
}

SoundMgr* SoundMgr::getInstance()
{
	if (!instance) instance = new SoundMgr{};
	return instance;
}

void SoundMgr::init()
{
	m_engine = createIrrKlangDevice();
	sound = make_unique<map<SOUND, int>>();

	if (!m_engine) cout << "Sound Initialization failed. \n";

	sound->emplace(SOUND::DAMAGED_PLAYER, CreateShortSound("./Sounds/DAMAGED_PLAYER.mp3"));
	sound->emplace(SOUND::FIRE_BULLET, CreateShortSound("./Sounds/FIRE_BULLET.mp3"));
	sound->emplace(SOUND::DESTROY_PLAYER, CreateShortSound("./Sounds/DESTROY_PLAYER.mp3"));
	sound->emplace(SOUND::DESTROY_ROCK, CreateShortSound("./Sounds/DESTROY_ROCK.mp3"));
	sound->emplace(SOUND::DESTROY_ENEMY1, CreateShortSound("./Sounds/DESTROY_ENEMY1.mp3"));
	sound->emplace(SOUND::DESTROY_ENEMY2, CreateShortSound("./Sounds/DESTROY_ENEMY2.mp3"));
	sound->emplace(SOUND::DESTROY_ENEMY3, CreateShortSound("./Sounds/DESTROY_ENEMY3.mp3"));
	sound->emplace(SOUND::DESTROY_ENEMY4, CreateShortSound("./Sounds/DESTROY_ENEMY4.mp3"));
	sound->emplace(SOUND::DESTROY_ENEMY5, CreateShortSound("./Sounds/DESTROY_ENEMY5.mp3"));
	sound->emplace(SOUND::YELL_ENEMY1, CreateShortSound("./Sounds/YELL_ENEMY1.mp3"));
	sound->emplace(SOUND::YELL_ENEMY2, CreateShortSound("./Sounds/YELL_ENEMY2.mp3"));
	sound->emplace(SOUND::YELL_ENEMY3, CreateShortSound("./Sounds/YELL_ENEMY3.mp3"));
	sound->emplace(SOUND::YELL_ENEMY4, CreateShortSound("./Sounds/YELL_ENEMY4.mp3"));

	sound->emplace(SOUND::TITLE, CreateBGSound("./Sounds/TITLE.mp3"));
	sound->emplace(SOUND::IN_GAME, CreateBGSound("./Sounds/IN_GAME.mp3"));
}

int SoundMgr::CreateBGSound(char* filePath)
{
	int index = 0;

	for (int i = 1; i < MAX_SOUND; i++)
	{
		if (m_bgSoundList.find(i) == m_bgSoundList.end())
		{
			index = i;
			break;
		}
	}
	ISound* tempSound = m_engine->play2D(filePath, false, true, true);
	if (tempSound == NULL)
	{
		std::cout << "Sound creation fails. \n";
		return -1;
	}
	m_bgSoundList.insert(std::pair<int, ISound*>(index, tempSound));

	return index;
}

void SoundMgr::DeleteBGSound(int index)
{
	std::map<int, ISound*>::iterator iter;

	iter = m_bgSoundList.find(index);

	if (iter == m_bgSoundList.end())
	{
		std::cout << "No such sound with index " << index << ". \n";
		return;
	}
	(*iter).second->stop();
	m_bgSoundList.erase(index);
}

void SoundMgr::PlayBGSound(int index, bool bLoop, float volume)
{
	std::map<int, ISound*>::iterator iter;

	iter = m_bgSoundList.find(index);

	if (iter == m_bgSoundList.end())
	{
		std::cout << "No such sound with index " << index << ". \n";
		return;
	}
	(*iter).second->setVolume(volume); 
	(*iter).second->setPlayPosition(0);
	(*iter).second->setIsPaused(false); 
	(*iter).second->setIsLooped(bLoop);
}

void SoundMgr::StopBGSound(int index)
{
	std::map<int, ISound*>::iterator iter;

	iter = m_bgSoundList.find(index);

	if (iter == m_bgSoundList.end())
	{
		std::cout << "No such sound with index " << index << ". \n";
		return;
	}
	(*iter).second->setIsPaused(true);
}

int SoundMgr::CreateShortSound(char* filePath)
{
	int index = 0;

	for (int i = 1; i < MAX_SOUND; i++)
	{
		if (m_shortSoundList.find(i) == m_shortSoundList.end())
		{
			index = i;
			break;
		}
	}
	ISoundSource* tempSound = m_engine->addSoundSourceFromFile(filePath);
	if (tempSound == NULL)
	{
		std::cout << "Sound creation fails. \n";
		return -1;
	}
	m_shortSoundList.insert(std::pair<int, ISoundSource*>(index, tempSound));

	return index;
}

void SoundMgr::DeleteShortSound(int index)
{
	std::map<int, ISoundSource*>::iterator iter;

	iter = m_shortSoundList.find(index);

	if (iter == m_shortSoundList.end())
	{
		std::cout << "No such sound with index " << index << ". \n";
		return;
	}
	m_shortSoundList.erase(index);
}

void SoundMgr::PlayShortSound(int index, bool bLoop, float volume)
{
	std::map<int, ISoundSource*>::iterator iter;

	iter = m_shortSoundList.find(index);

	if (iter == m_shortSoundList.end())
	{
		std::cout << "No such sound with index " << index << ". \n";
		return;
	}
	(*iter).second->setDefaultVolume(volume);
	m_engine->play2D((*iter).second, bLoop);
}

int SoundMgr::getSound(SOUND name) const
{
	return (*sound)[name];
}
