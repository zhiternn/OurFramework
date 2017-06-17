#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "SceneBase3D.h"

class ShaderProgram;
class SceneManager;
class TextEntity;
class Light;
class SceneTemplate3D : public SceneBase3D
{
public:
	SceneTemplate3D();
	~SceneTemplate3D();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	SceneTemplate3D(SceneManager* _sceneMgr); // This is used to register to SceneManager

	CPlayerInfo* playerInfo;
	GroundEntity* groundEntity;

	GenericEntity* theCube;

	static SceneTemplate3D* sInstance; // The pointer to the object that gets registered
};

#endif