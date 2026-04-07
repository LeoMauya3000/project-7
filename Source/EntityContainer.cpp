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
//#include "Collider.h"
#define MAXENTITYENTRY 100
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct EntityContainer
{
	// This variable is not required but could be used for tracking the number
	//   of Entities currently in the list.  Instructions on how to do this
	//   are included in the function headers.
	unsigned entityCount;

	// This variable is not required but could be used for different purposes.
	// - For storing the maximum size of the container.
	// - For tracking peak usage of the container, used for testing purposes.
	unsigned entityMax;

	// This list can be a fixed-length array (minimum size of 100 entries)
	// or a dynamically sized array, such as a linked list.
	// (NOTE: The implementation details are left up to the student.  However,
	//    it is your responsiblity to ensure that memory is handled correctly.)
	Entity* entities[MAXENTITYENTRY];

} EntityContainer;

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

EntityContainer* EntityContainerCreate()
{
	EntityContainer* returnedEntityContainer = calloc(1, sizeof(EntityContainer));
	if (returnedEntityContainer)
	{
		returnedEntityContainer->entityMax = MAXENTITYENTRY;
		for (int i = 0; i < MAXENTITYENTRY; i++)
		{
			returnedEntityContainer->entities[i] = 0;
		}
		return returnedEntityContainer;
	}
	
	return NULL;
	
}
void EntityContainerFree(EntityContainer** entities)
{
	if (entities && *entities)
	{
	 free(*entities);
	 *entities = NULL;

	}
	//yikes maybe 
	
}
bool EntityContainerAddEntity(EntityContainer* entities, Entity* entity)
{
     if(entities && entity)
	 {
		 if (entities->entityCount < entities->entityMax)
		 {
			 entities->entities[entities->entityCount] = entity;

			 if (entities->entities[entities->entityCount])
			 {
				 entities->entityCount++;
				 return true;
			 }
		 }
	 }
	 return false;
}

Entity* EntityContainerFindByName(const EntityContainer* entities, const char* entityName)
{

	if (entities && entityName) 
	{
		for (unsigned int i = 0; i < entities->entityCount; i++)
		{
			if (EntityIsNamed(entities->entities[i], entityName))
			{
				return entities->entities[i];
			}
		}
	}
	return NULL;
}
bool EntityContainerIsEmpty(const EntityContainer* entities)
{

	//technically a count of 0 means zero entites......
	if (entities)
	{
		if (entities->entityCount == 0)
		{
			return true;
		}
	}
	return false;
}
void EntityContainerUpdateAll(EntityContainer* entities, float dt)
{
	if (entities)
	{
		for (unsigned i = 0; i < entities->entityCount; i++)
		{
			if (entities->entities[i])
			{
			 EntityUpdate(entities->entities[i],dt);

			}
			if (EntityIsDestroyed(entities->entities[i]))
			{
		
				EntityFree(&entities->entities[i]);
				for (unsigned int j = i; j < entities->entityCount - 1; j++)
				{
					entities->entities[j] = entities->entities[j + 1];
				}
				entities->entityCount--;
				i--;
			}
		}
	}
}
void EntityContainerRenderAll(const EntityContainer* entities)
{
	if (entities)
	{
		for (unsigned int i = 0; i < entities->entityCount; i++)
		{
			  EntityRender(entities->entities[i]);
		}
	}
}
void EntityContainerFreeAll(EntityContainer* entities)
{
	if (entities)
	{
		for (unsigned int i = 0; i < entities->entityCount; i++)
		{
			if (entities->entities[i]) 
			{
				EntityFree(&entities->entities[i]);
			}
		}
		entities->entityCount = 0;
	}
}

void EntityContainerCheckCollisions(EntityContainer* entities)
{
	if (entities)
	{
		Entity* entityA = NULL;
		Entity* entityB = NULL;

		for (unsigned int i = 0; i < entities->entityCount; i++)
		{
				if (entities->entities[i] && EntityGetCollider(entities->entities[i]))
				{
					entityA = entities->entities[i];
					for (unsigned int j = i + 1; j < entities->entityCount; j++)
					{
						if (!entityB)
						{
							if (entities->entities[j] && EntityGetCollider(entities->entities[j]))
							{
								entityB = entities->entities[j];
							}
						}

						if (entityA && entityB)
						{
							ColliderCheck(EntityGetCollider(entityA), EntityGetCollider(entityB));
					
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

