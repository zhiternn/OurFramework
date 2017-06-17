#ifndef SPRITE_ENTITY_H
#define SPRITE_ENTITY_H

#include "EntityBase.h"
#include "Vector3.h"
#include "Vertex.h"
#include "Animation.h"
#include <string>

class Mesh;

class SpriteEntity : public EntityBase
{
public:
	enum SPRITE_RENDERMODE
	{
		MODE_2D,
		MODE_3D,

		NUM_MODE
	};

	SpriteEntity(Mesh* _modelMesh);
	virtual ~SpriteEntity();

	virtual void Update(double dt);
	virtual void Render();
	virtual void RenderUI();

	inline void SetTextRenderMode(SPRITE_RENDERMODE _mode){ mode = _mode; };

	AnimationPlayer animationPlayer;
protected:
	Mesh* modelMesh;
	SPRITE_RENDERMODE mode;
};

namespace Create
{
	SpriteEntity* Sprite2DObject(const std::string& _meshName, const Vector3& _position, const Vector3& _scale = Vector3(1.0f,1.0f,1.0f));
	SpriteEntity* Sprite3DObject(const std::string& _meshName, const Vector3& _position, const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f));
};

#endif // SPRITE_ENTITY_H