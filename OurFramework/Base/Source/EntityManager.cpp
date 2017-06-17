#include "EntityManager.h"
#include "EntityBase.h"
#include "Collider/Collider.h"

#include <iostream>
using namespace std;

// Update all entities
void EntityManager::Update(double dt)
{
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	
	// Clean up entities that are done
	it = entityList.begin();
	while (it != entityList.end())
	{
		if ((*it)->IsDone())
		{
			// Delete if done
			//SceneGraph::GetInstance()->DeleteNode((*it));
			delete *it;
			it = entityList.erase(it);
		}
		else
		{
			// Move on otherwise
			++it;
		}
	}

	// Update all entities
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->Update(dt);
	}
	//SceneGraph::GetInstance()->Update();
	//if (spatialPartition)
	//	spatialPartition->Update();

	CheckForCollision(dt);
}

void EntityManager::HandleOutOfBounds(Vector3 min, Vector3 max, double dt)
{
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->HandleOutOfBounds(min, max, dt);
	}
}

void EntityManager::HandleOutOfBounds(Vector3 point, float radius, double dt)
{
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->HandleOutOfBounds(point, radius, dt);
	}
}

// Render all entities
void EntityManager::Render()
{
	// Render all entities
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->Render();
	}
}

// Render the UI entities
void EntityManager::RenderUI()
{
	// Render all entities UI
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->RenderUI();
	}
}

// Add an entity to this EntityManager
void EntityManager::AddEntity(EntityBase* _newEntity, bool bAddToSpatialPartition)
{
	entityList.push_back(_newEntity);
}

// Remove an entity from this EntityManager
bool EntityManager::RemoveEntity(EntityBase* _existingEntity)
{
	// Find the entity's iterator
	std::list<EntityBase*>::iterator findIter = std::find(entityList.begin(), entityList.end(), _existingEntity);

	// Delete the entity if found
	if (findIter != entityList.end())
	{
		delete *findIter;
		findIter = entityList.erase(findIter);

		return true;
	}
	// Return false if not found
	return false;
}

// Mark an entity for deletion
bool EntityManager::MarkForDeletion(EntityBase* _existingEntity)
{
	std::list<EntityBase*>::iterator findIter = std::find(entityList.begin(), entityList.end(), _existingEntity);

	// Delete entity if found
	if (findIter != entityList.end())
	{
		(*findIter)->SetIsDone(true);
		return true;
	}
	else
		return false;
}

std::list<EntityBase*> EntityManager::GetList()
{
	return entityList;
}

// Constructor
EntityManager::EntityManager()
{
}

// Destructor
EntityManager::~EntityManager()
{
}

// Check for overlap
bool EntityManager::CheckOverlap(Vector3 thisMinAABB, Vector3 thisMaxAABB, Vector3 thatMinAABB, Vector3 thatMaxAABB)
{
	if (((thatMinAABB >= thisMinAABB) && (thatMinAABB <= thisMaxAABB))
		||
		((thatMaxAABB >= thisMinAABB) && (thatMaxAABB <= thisMaxAABB)))
	{
		return true;
	}

	if (((thisMinAABB >= thatMinAABB) && (thisMinAABB <= thatMaxAABB))
		||
		((thisMaxAABB >= thatMinAABB) && (thisMaxAABB <= thatMaxAABB)))
	{
		return true;
	}

	if (((thisMinAABB >= thatMinAABB) && (thisMaxAABB <= thatMaxAABB))
		&&
		((thisMaxAABB >= thatMinAABB) && (thisMaxAABB <= thatMaxAABB)))
	{
		return true;
	}

	if (((thatMinAABB >= thisMinAABB) && (thatMinAABB <= thisMaxAABB))
		&&
		((thatMaxAABB >= thisMinAABB) && (thatMaxAABB <= thisMaxAABB)))
	{
		return true;
	}

	return false;
}

// Check if this entity's bounding sphere collided with that entity's bounding sphere 
bool EntityManager::CheckSphereCollision(EntityBase *ThisEntity, EntityBase *ThatEntity)
{
	CCollider *thisCollider = dynamic_cast<CCollider*>(ThisEntity);
	CCollider *thatCollider = dynamic_cast<CCollider*>(ThatEntity);

	if (!thisCollider || !thatCollider)
		return false;

	float totalRadius = thisCollider->GetMinAABB().x + thatCollider->GetMinAABB().x;

	if ((ThisEntity->GetPosition() - ThatEntity->GetPosition()).LengthSquared()
		<=
		totalRadius * totalRadius)
	{
		return true;
	}
	else
	{
		return false;
	}

	//if (DistanceSquaredBetween(thisMinAABB, thisMaxAABB) +
	//	DistanceSquaredBetween(thatMinAABB, thatMaxAABB)
	//	>
	//	DistanceSquaredBetween(ThisEntity->GetPosition(), ThatEntity->GetPosition()) * 2.0f)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}

// Check if this entity collided with another entity, but both must have collider
bool EntityManager::CheckAABBCollision(EntityBase *ThisEntity, EntityBase *ThatEntity)
{
	CCollider *thisCollider = dynamic_cast<CCollider*>(ThisEntity);
	CCollider *thatCollider = dynamic_cast<CCollider*>(ThatEntity);

	// Get the minAABB and maxAABB for each entity
	Vector3 thisMinAABB = ThisEntity->GetPosition() + thisCollider->GetMinAABB();
	Vector3 thisMaxAABB = ThisEntity->GetPosition() + thisCollider->GetMaxAABB();
	Vector3 thatMinAABB = ThatEntity->GetPosition() + thatCollider->GetMinAABB();
	Vector3 thatMaxAABB = ThatEntity->GetPosition() + thatCollider->GetMaxAABB();

	if (CheckOverlap(thisMinAABB, thisMaxAABB, thatMinAABB, thatMaxAABB))
		return true;
	
	Vector3 altThisMinAABB = Vector3(thisMinAABB.x, thisMinAABB.y, thisMaxAABB.z);
	Vector3 altThisMaxAABB = Vector3(thisMaxAABB.x, thisMaxAABB.y, thisMinAABB.z);

	if (CheckOverlap(altThisMinAABB, altThisMaxAABB, thatMinAABB, thatMaxAABB))
		return true;

	return false;
}

// Check if any Collider is colliding with another Collider
bool EntityManager::CheckForCollision(double dt)
{
	std::list<EntityBase*>::iterator colliderThis, colliderThisEnd;
	std::list<EntityBase*>::iterator colliderThat, colliderThatEnd;

	colliderThisEnd = entityList.end();
	for (colliderThis = entityList.begin(); colliderThis != colliderThisEnd; ++colliderThis)
	{
		if ((*colliderThis)->HasCollider())
		{
			EntityBase *thisEntity = dynamic_cast<EntityBase*>(*colliderThis);

			colliderThatEnd = entityList.end();

			for (colliderThat = colliderThis; colliderThat != colliderThatEnd; ++colliderThat)
			{
				if (colliderThat == colliderThis)
					continue;

				if ((*colliderThat)->HasCollider())
				{
					EntityBase *thatEntity = dynamic_cast<EntityBase*>(*colliderThat);
					if (CheckSphereCollision(thisEntity, thatEntity) == true)
					{
						thisEntity->HandleCollision(thatEntity, dt);
						thatEntity->HandleCollision(thisEntity, dt);
					}
				}
			}
		}
	}

	return false;
}
