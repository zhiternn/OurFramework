#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "SingletonTemplate.h"
#include <list>
#include "Vector3.h"

class EntityBase;

class EntityManager : public Singleton<EntityManager>
{
	friend Singleton<EntityManager>;
public:
	virtual void Update(double dt);
	void Render();
	void RenderUI();
	void HandleOutOfBounds(Vector3 min, Vector3 max, double dt);
	void HandleOutOfBounds(Vector3 point, float radius, double dt);

	void AddEntity(EntityBase* _newEntity, bool bAddToSpatialPartition = false);
	bool RemoveEntity(EntityBase* _existingEntity);
	bool MarkForDeletion(EntityBase* _existingEntity);

	std::list<EntityBase*> GetList();

protected:
	EntityManager();
	virtual ~EntityManager();

	// Check for overlap
	bool CheckOverlap(Vector3 thisMinAABB, Vector3 thisMaxAABB, Vector3 thatMinAABB, Vector3 thatMaxAABB);
	// Check if this entity's bounding sphere collided with that entity's bounding sphere 
	bool CheckSphereCollision(EntityBase *ThisEntity, EntityBase *ThatEntity);
	// Check if this entity collided with another entity, but both must have collider
	bool CheckAABBCollision(EntityBase *ThisEntity, EntityBase *ThatEntity);
	// Check if any Collider is colliding with another Collider
	bool CheckForCollision(double dt);

	std::list<EntityBase*> entityList;
};

#endif // ENTITY_MANAGER_H