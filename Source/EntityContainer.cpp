//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "EntityContainer.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Collider.h"
//#include "Collider.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
bool ColliderIsColliding(const Collider* collider, const Collider* other);
// Initialize the ...
void EntityContainerInit()
{
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void EntityContainerUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);
}

// Shutdown the ...
void EntityContainerExit()
{
}

//EntityContainer::EntityContainer()
//{
//
//}
 EntityContainer::~EntityContainer()
{
	 EntityContainerFreeAll();
}
bool EntityContainer::EntityContainerAddEntity(Entity* entity)
{
     if(entity)
	 {
		 if (this->entityCount < this->entityMax)
		 {
			 this->entities.push_back(entity);
			 this->entityCount++;
			 return true;
		 }
	 }
	 return false;
}

Entity* EntityContainer::EntityContainerFindByName( const char* entityName)
{
	if (entityName) 
	{
		for (auto entity : entities)
		{
			if (entity)
			{
				if (entity->EntityIsNamed(entityName))
				{
					return entity;
				}
			}
		}
	}
	return NULL;
}
bool EntityContainer::EntityContainerIsEmpty() const
{
	if (this->entityCount == 0)
	{
		return true;
	}
	return false;
}
void EntityContainer::EntityContainerUpdateAll( float dt)
{
	if (this)
	{
		for (auto entity = entities.begin(); entity != entities.end();)
		{
			if (*entity)
			{
				(*entity)->EntityUpdate(dt);

				if ((*entity)->EntityIsDestroyed())
				{

					delete* entity;
					entity = entities.erase(entity);
					--entityCount;
					continue;
				}
			}
			  ++entity;
			
		}
	}
}
void EntityContainer::EntityContainerRenderAll()
{
	if (this)
	{
		for (auto entity : entities)
		{
			if (entity)
			{
				entity->EntityRender();
			}
		}
	}
}
void EntityContainer::EntityContainerFreeAll()
{
	if (this)
	{
		for (auto entity : entities)
		{
			
			
				delete entity;
			
		}
		this->entities.clear();
		this->entityCount = 0;
	}
}

void EntityContainer::ColliderCheck(const Collider* collider, const Collider* other)
{
	if (collider && other)
	{
		if (ColliderIsColliding(collider, other))
		{
			if (collider->ReturnHandler())
			{
				collider->ReturnHandler()(collider->Parent(), other->Parent());
			}
			if (other->ReturnHandler())
			{
				other->ReturnHandler()(other->Parent(), collider->Parent());
			}
		}
	}
}

void EntityContainer::EntityContainerCheckCollisions()
{

	
	if (this)
	{
		Entity* entityA = NULL;
		Entity* entityB = NULL;
		

		for (unsigned int i = 0; i < this->entityCount; ++i)
		{
				if (this->entities[i] && this->entities[i]->Has(Collider))
				{
					entityA = this->entities[i];
					for (unsigned int j = i + 1; j < this->entityCount; j++)
					{
						if (!entityB)
						{
							if (entities[j] && this->entities[j]->Has(Collider))
							{
								entityB = this->entities[j];
							}
						}

						if (entityA && entityB)
						{
							this->ColliderCheck(entityA->Has(Collider), entityB->Has(Collider));
							entityB = NULL;
						}
					}
					
				}
		}
	}
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

