#include "SpriteEntity.h"

#include "MeshBuilder.h"
#include "EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

SpriteEntity::SpriteEntity(Mesh* _modelMesh) :
modelMesh(_modelMesh),
mode(MODE_2D)
{
	animationPlayer.m_currentFrame = Math::RandIntMinMax(100, 200);
	animationPlayer.m_anim = new Animation();
	animationPlayer.m_anim->Set(Math::RandIntMinMax(50, 100), Math::RandIntMinMax(101, 150), 1, 50.0f, true);

	position.Set(0.0f, 0.0f, 0.0f);
	scale.Set(1.0f, 1.0f, 1.0f);
}

SpriteEntity::~SpriteEntity()
{
}

void SpriteEntity::Update(double dt)
{
	animationPlayer.Update(dt);
}

void SpriteEntity::Render()
{
	if (mode == MODE_2D)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderSprite(modelMesh, animationPlayer);
	modelStack.PopMatrix();
}

void SpriteEntity::RenderUI()
{
	if (mode == MODE_3D)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderSprite(modelMesh, animationPlayer);
	modelStack.PopMatrix();
}

SpriteEntity* Create::Sprite2DObject(const std::string& _meshName, const Vector3& _position, const Vector3& _scale)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	SpriteEntity* result = new SpriteEntity(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);
	result->SetTextRenderMode(SpriteEntity::MODE_2D);
	EntityManager::GetInstance()->AddEntity(result);
	return result;
}

SpriteEntity* Create::Sprite3DObject(const std::string& _meshName, const Vector3& _position, const Vector3& _scale)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	SpriteEntity* result = new SpriteEntity(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);
	result->SetTextRenderMode(SpriteEntity::MODE_3D);
	EntityManager::GetInstance()->AddEntity(result);
	return result;
}