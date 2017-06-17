#include "SceneTemplate2D.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "KeyboardController.h"
#include "MouseController.h"
#include "SceneManager.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "EntityManager.h"

#include "GenericEntity.h"
#include "GroundEntity.h"
#include "TextEntity.h"
#include "SpriteEntity.h"
#include "Light.h"
#include "SkyBox/SkyBoxEntity.h"

#include <iostream>
using namespace std;

SceneTemplate2D* SceneTemplate2D::sInstance = new SceneTemplate2D(SceneManager::GetInstance());

SceneTemplate2D::SceneTemplate2D()
{
}

SceneTemplate2D::SceneTemplate2D(SceneManager* _sceneMgr)
{
	_sceneMgr->AddScene("SceneTemplate2D", this);
}

SceneTemplate2D::~SceneTemplate2D()
{
}

void SceneTemplate2D::Init()
{
	SceneBase2D::Init();

	orthoHeight;
	orthoWidth;
	worldHeight = 100;
	worldWidth = worldHeight * ((float)Application::GetInstance().GetWindowWidth() / Application::GetInstance().GetWindowHeight());

	// Create the playerinfo instance, which manages all information about the player
	playerInfo = CPlayerInfo::GetInstance();
	playerInfo->Init();

	// Create entities into the scene
	Create::Entity("axis", Vector3(0.0f, 0.0f, 0.0f)); // Reference
	Create::Entity("lightball", Vector3(lights[0]->position.x, lights[0]->position.y, lights[0]->position.z)); // Lightball
	GenericEntity* aCube = Create::Entity("cube", Vector3(-20.0f, 0.0f, -20.0f));

}

void SceneTemplate2D::Update(double dt)
{
	SceneBase2D::Update(dt);

	// if the left mouse button was released
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB))
	{
		cout << "Left Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::RMB))
	{
		cout << "Right Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::MMB))
	{
		cout << "Middle Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) != 0.0)
	{
		cout << "Mouse Wheel has offset in X-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) << endl;
	}
	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) != 0.0)
	{
		cout << "Mouse Wheel has offset in Y-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) << endl;
	}
}

void SceneTemplate2D::Render()
{
	SceneBase2D::Render();
}

void SceneTemplate2D::Exit()
{
	playerInfo->DetachCamera();

	if (playerInfo->DropInstance() == false)
	{
#if _DEBUGMODE==1
		cout << "Unable to drop PlayerInfo class" << endl;
#endif
	}
	SceneBase2D::Exit();
}
