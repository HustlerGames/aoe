#pragma once

#include <windows.h>
#include <fileapi.h>
#include <xaudio2.h>
#include "World/sounds.h"

#define SOUND_PLAYING 1
#define SOUND_STOPPED 2

class GameSound {
public:
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	WAVEFORMATEXTENSIBLE wfx = { 0 };
	XAUDIO2_BUFFER buffer = { 0 };
	int state = SOUND_STOPPED;
	~GameSound();
};

class AudioSystem
{
public:
	
	AudioSystem();
	~AudioSystem();
	bool init();
	bool LoadSound(unsigned int id, const TCHAR* filename);
	void play(unsigned int id);
private:
	
	IXAudio2* pXAudio2 = nullptr;
	IXAudio2MasteringVoice* pMasterVoice = nullptr;

	GameSound* sounds[SOUND_COUNT] = {0};
	GameSound* createSound(const TCHAR* filename);
	void loadSounds();
};