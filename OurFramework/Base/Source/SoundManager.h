#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "SingletonTemplate.h"

#include <map>
#include <string>

#include <irrKlang.h>
using namespace irrklang;

struct Vector3;

class SoundManager : public Singleton<SoundManager>
{
	friend Singleton<SoundManager>;
public:
	void Init();
	void Exit();

	void PlaySound2D(const std::string &soundName);
	void PlaySound3D(const std::string &soundName, Vector3 soundPos);

	void LoadMedia(const std::string &soundName, char* fileLocation, float minDist = 0.0f, float maxDist = 0.0f);

private:
	SoundManager();
	~SoundManager();

	ISoundEngine* activeSoundEngine;

	std::map<std::string, ISoundSource*> soundMap;
};

#endif