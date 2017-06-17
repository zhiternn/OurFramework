#ifndef SCENE_TEXT2_H
#define SCENE_TEXT2_H

#include "SceneBase2D.h"

class ShaderProgram;
class SceneManager;
class TextEntity;
class Light;
class SceneTemplate2D : public SceneBase2D
{
public:
	SceneTemplate2D();
	~SceneTemplate2D();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	SceneTemplate2D(SceneManager* _sceneMgr); // This is used to register to SceneManager

	CPlayerInfo* playerInfo;

	GenericEntity* theCube;

	static SceneTemplate2D* sInstance; // The pointer to the object that gets registered
};

#endif