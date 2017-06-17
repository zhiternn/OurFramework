#ifndef SCENE_BASE_3D_H
#define SCENE_BASE_3D_H

#include "Scene.h"
#include "Mtx44.h"
#include "PlayerInfo/PlayerInfo.h"
#include "GroundEntity.h"
#include "FPSCamera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "GenericEntity.h"

class ShaderProgram;
class SceneManager;
class TextEntity;
class Light;
class SceneBase3D : public Scene
{
public:
	SceneBase3D();
	~SceneBase3D();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	ShaderProgram* currProg;
	FPSCamera camera;
	TextEntity* textObj[3];
	Light* lights[2];
};

#endif