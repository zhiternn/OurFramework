#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <string>
#include <map>

class Mesh;
class Animation;

class AnimationManager
{
public:
	static AnimationManager* GetInstance(const std::string& meshName)
	{
		if (instance.count(meshName) == 0)
			instance[meshName] = new AnimationManager();

		return instance[meshName];
	}
	static AnimationManager* RemoveInstance(const std::string& meshName)
	{
		AnimationManager* currMesh = GetInstance(meshName);
		if (currMesh != NULL)
		{
			delete currMesh;
			instance.erase(meshName);
		}
	}
	static void Destroy()
	{
		for (auto q : instance)
		{
			AnimationManager* currID = q.second;
			if (currID != NULL)
			{
				delete currID;
				instance.erase(q.first);
			}
		}
	}
	virtual ~AnimationManager();

	Animation* GetAnimation(const std::string& animName);
	void AddAnimation(const std::string& animName, Animation* anim);
	void RemoveAnimation(const std::string& animName);

protected:
	AnimationManager();

	std::map<std::string, Animation*> animMap;

	static std::map<std::string, AnimationManager*> instance;
};

#endif