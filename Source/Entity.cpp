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
#include "Component.h"
//#include "Behavior.h"
//#include "BehaviorSpaceship.h"
//#include "BehaviorBullet.h"
//#include "Collider.h"
//#include "BehaviorAsteroid.h"
//#include "BehaviorHudText.h"
//#include "ColliderCircle.h"
//#include "ColliderLine.h"


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


//void Entity::EntityRead(Entity* entity, Stream stream)
//{
//	const char* token = StreamReadToken(stream);
//	EntitySetName(entity, token);
//
//	if (entity && stream)
//	{
//		token = StreamReadToken(stream);
//		while(token)
//		{
//			if (!strncmp(token, "Transform", _countof("Transform")))
//			{
//				entity->transform = TransformCreate();
//				TransformRead(entity->transform, stream);
//				
//			}
//			else if (!strncmp(token, "Physics", _countof("Physics")))
//			{
//				entity->physics = PhysicsCreate();
//				PhysicsRead(entity->physics, stream);
//			}
//			else if (!strncmp(token, "Sprite", _countof("Sprite")))
//			{
//				entity->sprite = SpriteCreate();
//				SpriteRead(entity->sprite, stream);
//			}
//			else if (!strncmp(token, "Animation", _countof("Animation")))
//			{
//
//				entity->animation = AnimationCreate();
//				AnimationRead(entity->animation, stream);
//				EntityAddAnimation(entity, entity->animation);
//			}
//			else if (!strncmp(token, "BehaviorSpaceship", _countof("BehaviorSpaceship")))
//			{
//
//				entity->behavior = BehaviorSpaceshipCreate();
//				BehaviorRead(entity->behavior, stream);
//				EntityAddBehavior(entity, entity->behavior);
//			}
//			else if (!strncmp(token, "BehaviorBullet", _countof("BehaviorBullet")))
//			{
//				entity->behavior = BehaviorBulletCreate();
//				BehaviorRead(entity->behavior, stream);
//				EntityAddBehavior(entity, entity->behavior);
//			}
//			else if (!strncmp(token, "BehaviorAsteroid", _countof("BehaviorAsteroid")))
//			{
//				entity->behavior = BehaviorAsteroidCreate();
//				BehaviorRead(entity->behavior, stream);
//				EntityAddBehavior(entity, entity->behavior);
//			}
//			else if (!strncmp(token, "BehaviorHudText", _countof("BehaviorHudText")))
//			{
//				entity->behavior = BehaviorHudTextCreate();
//				BehaviorHudTextRead(entity->behavior, stream);
//				EntityAddBehavior(entity, entity->behavior);
//			}
//			else if (!strncmp(token, "ColliderCircle", _countof("ColliderCircle")))
//			{
//				entity->collider = ColliderCircleCreate();
//				ColliderCircleRead(entity->collider, stream);
//				EntityAddCollider(entity, entity->collider);
//			}
//			else if (!strncmp(token, "ColliderLine", _countof("ColliderLine")))
//			{
//				entity->collider = ColliderLineCreate();
//				ColliderLineRead(entity->collider, stream);
//				EntityAddCollider(entity, entity->collider);
//			}
//			else if (strcmp(token, "") == 0)
//			{
//				return;
//			}
//		
//			 token = StreamReadToken(stream);
//		}
//			
//	}
//}


void Entity::EntityAddComponent(Component* component)
{
	if (component)
	{
		component->Parent(this);
		components.push_back(component);
	}
}
void Entity::EntitySetName(const char* _name)
{
	if (_name)
	{
		strcpy_s(this->name, name);
	}
}
const char* Entity::EntityGetName()
{
	return this->name;
}
void Entity::EntityUpdate(float dt)
{
	for (auto component : components)
	{
		component->Update(dt);
	}
}
void Entity::EntityRender()
{
	for (auto component : components)
	{
		component->Render();
	}
}


Entity& Entity::EntityClone(const Entity* other)
{
		return *this = *other;	
}
void Entity::EntityRead(Stream stream)
{
	const char* token = StreamReadToken(stream);
	this->EntitySetName(token);
	while (token)
	{

		if (!strncmp(token, "Transform", _countof("Transform")))
		{
			Transform* transform = new Transform();
			transform->TransformRead(stream);
			this->EntityAddComponent(transform);
		}
		else if (!strncmp(token, "Physics", _countof("Physics")))
		{
			Physics* physics = new Physics();
			physics->PhysicsRead(stream);
			this->EntityAddComponent(physics);
		}
		else if (!strncmp(token, "Sprite", _countof("Sprite")))
		{
			Sprite* sprite = new Sprite();
			sprite->SpriteRead(stream);
			this->EntityAddComponent(sprite);
		}
		else if (!strncmp(token, "Animation", _countof("Animation")))
		{

			Animation* animation = new Animation();
			animation->AnimationRead(stream);
			this->EntityAddComponent(animation);
		}
		else if (strcmp(token, "") == 0)
		{
			return;
		}

		token = StreamReadToken(stream);
	}
}
void Entity::EntityDestroy()
{
	this->isDestroyed = true;
}
bool Entity::EntityIsDestroyed() const
{
	if (this->isDestroyed)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Entity::EntityIsNamed( const char* _name) const
{
	if (strcmp(this->name, _name) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}			
}
Entity::Entity(char* _name, bool isDestroyed)
{
	this->isDestroyed = isDestroyed;
	strcpy_s(this->name, _countof(this->name), _name);
}
Entity::Entity() 
{
	this->isDestroyed = false;
	strcpy_s(this->name, "blank");
}

Entity::~Entity()
{
	for (Component* component : components) 
	{
		delete component;
	}
	components.clear();
}
Component* Entity::Get(Component::TypeEnum type) const
{
	for (Component* component : components)
	{
		if (component->Type() == type)
		{
			return component;
		}
	}

	return NULL;
	
}





