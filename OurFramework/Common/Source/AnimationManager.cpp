#include "AnimationManager.h"
#include "Animation.h"

std::map<std::string, AnimationManager*> AnimationManager::instance;

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
}

Animation* AnimationManager::GetAnimation(const std::string& animName)
{
	if (animMap.count(animName) != 0)
		return animMap[animName];
	else
		return NULL;
}

void AnimationManager::AddAnimation(const std::string& animName, Animation* anim)
{
	// Trivial Rejection : Invalid pointer provided
	if (anim == NULL)
		return;

	// Clean up first if there is an existing mesh with the same name
	RemoveAnimation(animName);

	// Add the mesh now
	animMap[animName] = anim;
}

void AnimationManager::RemoveAnimation(const std::string& animName)
{
	Animation* currMesh = GetAnimation(animName);
	if (currMesh != nullptr)
	{
		delete currMesh;
		animMap.erase(animName);
	}
}