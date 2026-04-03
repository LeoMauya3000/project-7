//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceShip.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorSpaceShip.h"
#include "Behavior.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "DGL.h"
#include "Physics.h"
#include "Transform.h"
#include "Entity.h"
#include "Vector2D.h"
#include "EntityFactory.h"
#include "EntityContainer.h"
#include "Scene.h"
#include "Teleporter.h"
#include "Collider.h"
#include "Sprite.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef enum spaceShipStates
{
	cSpaceshipInvalid = -1,
	cSpaceshipIdle,
	cSpaceshipThrust,
	cSpaceshipDead

}spaceShipStates;


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
	static const float spaceshipAcceleration = 150.0f;
    static const float spaceshipSpeedMax = 500.0f;
	static const float spaceshipTurnRateMax = (float)M_PI / 1.5f;
	static const float spaceshipWeaponCooldownTime = 0.25f;
	static const float spaceshipWeaponBulletSpeed = 750.0f;
	static const float spaceshipDeathDuration = 3.0f;
	static EntityContainer * entityList;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
		static void BehaviorSpaceshipOnInit(Behavior* behavior);
		static void BehaviorSpaceshipOnUpdate(Behavior* behavior, float dt);
		static void BehaviorSpaceshipOnExit(Behavior* behavior);
		static void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt);
		static void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt);
		static void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt);
		static void BehaviorSpaceshipSpawnBullet(Behavior* behavior);
	    static void BehaviorSpaceshipCollisionHandler(Entity* entity1, const Entity* entity2);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


Behavior* BehaviorSpaceshipCreate(void)
{
	Behavior* spaceShipBehavior = calloc(1, sizeof(Behavior));
	if (spaceShipBehavior)
	{
		spaceShipBehavior->stateCurr = cSpaceshipInvalid;
		spaceShipBehavior->stateNext = cSpaceshipInvalid;
		spaceShipBehavior->memorySize = sizeof(Behavior);
		spaceShipBehavior->onInit = &BehaviorSpaceshipOnInit;
		spaceShipBehavior->onUpdate = &BehaviorSpaceshipOnUpdate;
		spaceShipBehavior->onExit = &BehaviorSpaceshipOnExit;
		return spaceShipBehavior;
	}
	return NULL;	
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void BehaviorSpaceshipOnInit(Behavior* behavior)
{

	if (behavior)
	{
		if (behavior->stateCurr == cSpaceshipIdle)
		{
			Collider* behaviorCollider = EntityGetCollider(behavior->parent);
			if (behaviorCollider)
			{
				ColliderSetCollisionHandler(behaviorCollider, BehaviorSpaceshipCollisionHandler);
			}
		}
		if (behavior->stateCurr == cSpaceshipDead)
		{
			behavior->timer = spaceshipDeathDuration;
		}
	}
}
static void BehaviorSpaceshipOnUpdate(Behavior* behavior, float dt)
{
	switch (behavior->stateCurr)
	{
	  case cSpaceshipIdle:
	  {
		  BehaviorSpaceshipUpdateRotation(behavior, dt);
		  BehaviorSpaceshipUpdateWeapon(behavior, dt);
		  if (DGL_Input_KeyDown(VK_UP))
		  {
			  behavior->stateNext = cSpaceshipThrust;
		  }
		  break;
	  }
		  
	  case cSpaceshipThrust:
	  {
		  BehaviorSpaceshipUpdateRotation(behavior, dt);
		  BehaviorSpaceshipUpdateVelocity(behavior, dt);
		  BehaviorSpaceshipUpdateWeapon(behavior, dt);
		  if (!DGL_Input_KeyDown(VK_UP))
		  {
			  behavior->stateNext = cSpaceshipIdle;
		  }
		  break;
	  }  
	  case cSpaceshipDead: 
	  {
		  behavior->timer -= dt;
		  if (behavior->timer < 0)
		  {
			  SceneRestart();
		  }
		  else
		  {
			  Transform* parentTransform = EntityGetTransform(behavior->parent);
			  Sprite* parentSprite = EntityGetSprite(behavior->parent);
			  if (parentTransform && parentSprite)
			  {
				  float parentAlpha = SpriteGetAlpha(parentSprite);
				  Vector2D scale = *TransformGetScale(parentTransform);
				  float rotation = TransformGetRotation(parentTransform);
				  scale.x += 90 * dt;
				  scale.y += 130 * dt;	
				  rotation += 10 * dt;

				  TransformSetScale(parentTransform, &scale);
				  TransformSetRotation(parentTransform, rotation);
				  behavior->timer -= dt;
			      SpriteSetAlpha(parentSprite, parentAlpha -= dt);
			  }
		  }
	  }
	}

	TeleporterUpdateEntity(behavior->parent);
}
static void BehaviorSpaceshipOnExit(Behavior* behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}
static void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (behavior)
	{
		Physics* physicsComponent = EntityGetPhysics(behavior->parent);
		float rotationVelocity = PhysicsGetRotationalVelocity(physicsComponent);

		if (DGL_Input_KeyDown(VK_LEFT))
		{
			rotationVelocity = spaceshipTurnRateMax;
			PhysicsSetRotationalVelocity(physicsComponent, rotationVelocity);
		}
		else if (DGL_Input_KeyDown(VK_RIGHT))
		{
			rotationVelocity = -spaceshipTurnRateMax;
			PhysicsSetRotationalVelocity(physicsComponent, rotationVelocity);
		}
		else
		{
			PhysicsSetRotationalVelocity(physicsComponent, 0);
		}
	}
}
 void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt)
{
	if (behavior)
	{
		Physics *physcicsComponenet = EntityGetPhysics(behavior->parent);
		Transform *transformComponent = EntityGetTransform(behavior->parent);
		if (physcicsComponenet && transformComponent)
		{ 
			float speed;
			float scalar = spaceshipAcceleration * dt;
			float rotation = TransformGetRotation(transformComponent);
			Vector2D velocity = *PhysicsGetVelocity(physcicsComponenet);
			Vector2D unitVector;
			Vector2DFromAngleRad(&unitVector, rotation);
			Vector2DNormalize(&unitVector, &unitVector);
			Vector2DScaleAdd(&velocity, &unitVector, scalar,&velocity);
			speed = Vector2DLength(&velocity);
			float speedCap = spaceshipSpeedMax / speed;
			if (speed > spaceshipSpeedMax)
			{
				Vector2DScale(&velocity,&velocity, speedCap);
			}
			PhysicsSetVelocity(physcicsComponenet,&velocity);
		}

	}
}
static void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt)
{
	if (behavior->timer > 0)
	{
		behavior->timer -= dt;
		if (behavior->timer < 0)
		{
			behavior->timer = 0;
		}
    }
	if (DGL_Input_KeyDown(VK_SPACE))
	{
		if (behavior->timer <= 0)
		{
		
			BehaviorSpaceshipSpawnBullet(behavior);
			behavior->timer = spaceshipWeaponCooldownTime;
		}
	}
}
static void BehaviorSpaceshipSpawnBullet(Behavior* behavior)
{
	Entity *bullet = NULL;

	
	bullet = EntityFactoryBuild("Bullet");
	if (bullet)
	{

		Transform* SpaceShiptransformComponent = EntityGetTransform(behavior->parent);
		Physics* physicsComponentBullet = EntityGetPhysics(bullet);
		if (SpaceShiptransformComponent && physicsComponentBullet)
		{
			Vector2D SpaceShipPosition = *TransformGetTranslation(SpaceShiptransformComponent);
			float SpaceShipRotation = TransformGetRotation(SpaceShiptransformComponent);
			Transform* bulletTransformComponent = EntityGetTransform(bullet);
			Vector2D bulletPosition = SpaceShipPosition;
			Vector2D bulletVelocity = *PhysicsGetVelocity(physicsComponentBullet);
			Vector2D nomarlizedDirection;
			TransformSetRotation(bulletTransformComponent, SpaceShipRotation);
			Vector2DFromAngleRad(&nomarlizedDirection, SpaceShipRotation);
			Vector2DNormalize(&nomarlizedDirection, &nomarlizedDirection);
			Vector2DScale(&bulletVelocity, &nomarlizedDirection, spaceshipWeaponBulletSpeed);
			PhysicsSetVelocity(physicsComponentBullet, &bulletVelocity);
			TransformSetTranslation(bulletTransformComponent, &bulletPosition);
			SceneAddEntity(bullet);

		}
		return;
		
	}
}

static void BehaviorSpaceshipCollisionHandler(Entity* entity1, const Entity* entity2)
{
	if (entity1 && entity2)
	{
		if ((!strncmp(EntityGetName(entity2), "Asteroid", _countof("Asteroid"))))
		{
			Behavior* entity1Behavior = EntityGetBehavior(entity1);
			if (entity1Behavior)
			{
				entity1Behavior->stateNext = cSpaceshipDead;

			}
		}
		//do reflections here 
		if ((!strncmp(EntityGetName(entity2), "Arena", _countof("Arena"))))
		{
		

			printf("you hit the arena!! \n \n \n");
		}
	}
}

