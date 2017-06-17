#include "SoundManager.h"
#include "Vector3.h"
#include "GraphicsManager.h"
#include "Vector3.h"

SoundManager::SoundManager():
activeSoundEngine(NULL)
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::Init()
{
	activeSoundEngine = createIrrKlangDevice();
	if (!activeSoundEngine)
	{
		printf("Error starting up irrKlang sound engine\n");
		return; // error starting up the sound engine
	}
}

void SoundManager::PlaySound2D(const std::string &soundName)
{
	activeSoundEngine->play2D(soundMap[soundName]);
}

void SoundManager::PlaySound3D(const std::string &soundName, Vector3 soundPos)
{
	irrklang::vec3df pos(soundPos.x, soundPos.y, soundPos.z);
	Mtx44 viewMatrix = GraphicsManager::GetInstance()->GetViewMatrix();

	irrklang::vec3df listenerPos(viewMatrix.a[3], viewMatrix.a[7], viewMatrix.a[11]);
	irrklang::vec3df listenerView(viewMatrix.a[2], viewMatrix.a[6], viewMatrix.a[10]);
	activeSoundEngine->setListenerPosition(listenerPos, listenerView);

	activeSoundEngine->play3D(soundMap[soundName], pos);
}

void SoundManager::LoadMedia(const std::string &soundName, char* fileLocation, float minDist, float maxDist)
{
	if (!activeSoundEngine)
		return;

	soundMap[soundName] = activeSoundEngine->addSoundSourceFromFile(fileLocation);
	soundMap[soundName]->setDefaultMinDistance(minDist);
	soundMap[soundName]->setDefaultMaxDistance(maxDist);
	soundMap[soundName]->setDefaultVolume(0.2);
}

void SoundManager::Exit()
{
	if (activeSoundEngine != NULL)
		activeSoundEngine->drop();
}