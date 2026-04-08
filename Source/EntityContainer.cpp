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
//#include "Collider.h"
#define MAXENTITYENTRY 100
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

EntityContainer::EntityContainer()
{
		this->entityMax = MAXENTITYENTRY;
		for (auto& entity : entities)
		{
			entity = 0;
		}
		/*for (int i = 0; i < MAXENTITYENTRY; i++)
		{
			this->entities[i] = 0;
		}*/
	
}
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
			 this->entities[this->entityCount] = entity;

			 if (this->entities[this->entityCount])
			 {
				 this->entityCount++;
				 return true;
			 }
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
			if (entity->EntityIsNamed(entityName))
			{
				return entity;
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
		for (unsigned i = 0; i < this->entityCount; i++)
		{
			if (this->entities[i])
			{
				this->entities[i]->EntityUpdate(dt);

			}
			if (this->entities[i]->EntityIsDestroyed())
			{
		
				delete this->entities[i];
				for (unsigned int j = i; j < this->entityCount - 1; j++)
				{
					this->entities[j] = this->entities[j + 1];
				}
				this->entityCount--;
				i--;
			}
		}
}
void EntityContainer::EntityContainerRenderAll()
{
	if (this)
	{
		for (auto entity : entities)
		{
			entity->EntityRender();
		}
	}
}
void EntityContainer::EntityContainerFreeAll()
{
	if (this)
	{
		for (auto entity : entities)
		{
			if (entity) 
			{
				delete entity;
			}
		}
		this->entities.clear();
		this->entityCount = 0;
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
							ColliderCheck(entityA->Has(Collider), entityB->Has(Collider));
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

