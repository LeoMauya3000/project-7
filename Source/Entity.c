//------------------------------------------------------------------------------
//
// File Name:	Entity.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Entity.h"
#include "Physics.h"
#include "Sprite.h"
#include "Stream.h"
#include "Transform.h"
#include "Animation.h"
#include "Behavior.h"
#include "BehaviorSpaceship.h"
#include "BehaviorBullet.h"
#include "Collider.h"
#include "BehaviorAsteroid.h"
#include "BehaviorHudText.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"


//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Entity
{
	// The name of the entity.
	// A buffer is used to allow each entity to have a unique name.
	// The buffer is hardcoded to an arbitrary length that will be sufficient
	//	 for all CS230 assignments.  You may, instead, use dynamically-allocated
	//	 arrays for this purpose but the additional complexity is unnecessary
	//	 and it is your responsibility to ensure that the memory is successfully
	//	 allocated and deallocated in all possible situations.
	// [NOTE: When setting the name, use strcpy_s() to reduce the risk of
	//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
	//	 calling this function!  Instead, use the _countof() macro to get the
	//	 size of the "name" array.]
	char name[32];

	// Flag to indicate that the Entity should be destroyed after it has been updated.
	bool isDestroyed;

	// Pointer to an attached Animation component.
	Animation* animation;

	// Pointer to an attached Behavior component.
	Behavior* behavior;

	// Pointer to an attached Physics component.
	Physics* physics;

	// Pointer to an attached Sprite component.
	Sprite* sprite;

	// Pointer to an attached Transform component.
	Transform* transform;

	Collider* collider;

} Entity;



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

Entity* EntityCreate(void)
{

	Entity* entity = calloc(1, sizeof(Entity));
	if (entity)
	{

		return entity;
	}
	else
	{
		return NULL;
	}
}
void EntityFree(Entity** entity)
{
	if (entity && *entity)
	{
		if ((*entity)->animation)
		{
			AnimationFree(&(*entity)->animation);
		}
		if ((*entity)->transform)
		{
			TransformFree(&(*entity)->transform);
		}
		if ((*entity)->sprite)
		{
			SpriteFree(&(*entity)->sprite);
		}
		if ((*entity)->behavior)
		{
			BehaviorFree(&(*entity)->behavior);
		}
		if ((*entity)->physics)
		{
			PhysicsFree(&(*entity)->physics);
		}
		if ((*entity)->collider)
		{
			ColliderFree(&(*entity)->collider);
		}

		free(*entity);
		*entity = NULL;
	}

}
void EntityRead(Entity* entity, Stream stream)
{
	const char* token = StreamReadToken(stream);
	EntitySetName(entity, token);

	if (entity && stream)
	{
		token = StreamReadToken(stream);
		while(token)
		{
			if (!strncmp(token, "Transform", _countof("Transform")))
			{
				entity->transform = TransformCreate();
				TransformRead(entity->transform, stream);
				
			}
			else if (!strncmp(token, "Physics", _countof("Physics")))
			{
				entity->physics = PhysicsCreate();
				PhysicsRead(entity->physics, stream);
			}
			else if (!strncmp(token, "Sprite", _countof("Sprite")))
			{
				entity->sprite = SpriteCreate();
				SpriteRead(entity->sprite, stream);
			}
			else if (!strncmp(token, "Animation", _countof("Animation")))
			{

				entity->animation = AnimationCreate();
				AnimationRead(entity->animation, stream);
				EntityAddAnimation(entity, entity->animation);
			}
			else if (!strncmp(token, "BehaviorSpaceship", _countof("BehaviorSpaceship")))
			{

				entity->behavior = BehaviorSpaceshipCreate();
				BehaviorRead(entity->behavior, stream);
				EntityAddBehavior(entity, entity->behavior);
			}
			else if (!strncmp(token, "BehaviorBullet", _countof("BehaviorBullet")))
			{
				entity->behavior = BehaviorBulletCreate();
				BehaviorRead(entity->behavior, stream);
				EntityAddBehavior(entity, entity->behavior);
			}
			else if (!strncmp(token, "BehaviorAsteroid", _countof("BehaviorAsteroid")))
			{
				entity->behavior = BehaviorAsteroidCreate();
				BehaviorRead(entity->behavior, stream);
				EntityAddBehavior(entity, entity->behavior);
			}
			else if (!strncmp(token, "BehaviorHudText", _countof("BehaviorHudText")))
			{
				entity->behavior = BehaviorHudTextCreate();
				BehaviorHudTextRead(entity->behavior, stream);
				EntityAddBehavior(entity, entity->behavior);
			}
			else if (!strncmp(token, "ColliderCircle", _countof("ColliderCircle")))
			{
				entity->collider = ColliderCircleCreate();
				ColliderCircleRead(entity->collider, stream);
				EntityAddCollider(entity, entity->collider);
			}
			else if (!strncmp(token, "ColliderLine", _countof("ColliderLine")))
			{
				entity->collider = ColliderLineCreate();
				ColliderLineRead(entity->collider, stream);
				EntityAddCollider(entity, entity->collider);
			}
			else if (strcmp(token, "") == 0)
			{
				return;
			}
		
			 token = StreamReadToken(stream);
		}
			
	}
}
void EntityAddPhysics(Entity* entity, Physics* physics)
{
	if (entity && physics)
	{
	 entity->physics = physics;

	}
}
void EntityAddSprite(Entity* entity, Sprite* sprite)
{
	if (entity && sprite)
	{
	 entity->sprite = sprite;

	}
}
void EntityAddTransform(Entity* entity, Transform* transform)
{
	if (entity && transform)
	{
	  entity->transform = transform;

	}
}
void EntitySetName(Entity* entity, const char* name)
{
	if (entity && name)
	{
		strcpy_s(entity->name, _countof(entity->name), name);
	}
}
const char* EntityGetName(const Entity* entity)
{
    
	return entity->name;
}
Physics* EntityGetPhysics(const Entity* entity)
{
	if (entity)
	{
	 return entity->physics;
	}
	return NULL;
}
Sprite* EntityGetSprite(const Entity* entity)
{

	return entity->sprite;
}
Transform* EntityGetTransform(const Entity* entity)
{
	if (entity)
	{
		return entity->transform;
	}
	return NULL;

}
void EntityUpdate(Entity* entity, float dt)
{
	if (entity->animation)
	{
		AnimationUpdate(entity->animation, dt);
	}
	if (entity->behavior)
	{
		BehaviorUpdate(EntityGetBehavior(entity), dt);
	}

	if (entity->physics && entity->transform && entity->sprite)
	{
		PhysicsUpdate(entity->physics, entity->transform, dt);
	}
	
}
void EntityRender(Entity* entity)
{
	if (entity)
	{
		if (entity->sprite && entity->transform)
		{
		 SpriteRender(entity->sprite, entity->transform);
		}
	}
}


void EntityAddAnimation(Entity* entity, Animation* animation)
{
	if (entity && animation)
	{
		AnimationSetParent(animation, entity);
		entity->animation = animation;
	}
}

Animation* EntityGetAnimation(const Entity* entity)
	{
	if (entity)
	{
		Animation* entityAnimation = entity->animation;
		return entityAnimation;
	}
	else
	{
		return NULL;
	}
}

Entity* EntityClone(const Entity* other)
{
	if (other)
	{
		Entity* clonedEntity = calloc(1, sizeof(Entity));
		if (clonedEntity)
		{
			EntitySetName(clonedEntity, other->name);
			if (EntityGetTransform(other))
			{
				Transform* clonedTransform = TransformClone(other->transform);
				EntityAddTransform(clonedEntity, clonedTransform);
			}
			if (EntityGetPhysics(other))
			{
				Physics* clonedPhysics = PhysicsClone(other->physics);
				EntityAddPhysics(clonedEntity, clonedPhysics);
			}
			if (EntityGetSprite(other))
			{
				Sprite* clonedSprite = SpriteClone(other->sprite);
				EntityAddSprite(clonedEntity, clonedSprite);
			}
			if (EntityGetAnimation(other))
			{
				Animation* animation = AnimationClone(other->animation);
				EntityAddAnimation(clonedEntity, animation);
			}
			if (EntityGetBehavior(other))
			{
				Behavior* behvaior = BehaviorClone(other->behavior);
				EntityAddBehavior(clonedEntity, behvaior);
			}
			if (EntityGetCollider(other))
			{
				Collider* collider = ColliderClone(other->collider);
				EntityAddCollider(clonedEntity, collider);
			}

			return clonedEntity;
		}
	}
	return NULL;
}
void EntityDestroy(Entity* entity)
{
	if (entity)
	{
 		entity->isDestroyed = true;
	}
}
bool EntityIsDestroyed(const Entity* entity)
{
	if (entity)
	{
		if (entity->isDestroyed)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
void EntityAddBehavior(Entity* entity, Behavior* behavior)
{
	if (entity && behavior)
	{
		BehaviorSetParent(behavior, entity);
		entity->behavior = behavior;
	}
}
bool EntityIsNamed(const Entity* entity, const char* name)
{
	if (entity && name)
	{
		if (strcmp(entity->name, name) == 0)
		{
			return true;
		}
	}
	
	return false;
}
//absolutely change this 
Behavior* EntityGetBehavior(const Entity* entity)
{
	if (entity)
	{
		return entity->behavior;
	}
	return NULL;
}
Collider* EntityGetCollider(const Entity* entity)
{
	if (entity)
	{
		return entity->collider;
	}
	return NULL;
}

void EntityAddCollider(Entity* entity, Collider* collider)
{
	if (entity && collider)
	{
		ColliderSetParent(collider, entity);
		entity->collider = collider;
	}
}

