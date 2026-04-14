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

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

 void BehaviorSpaceship::onInit()
{

	if (this)
	{
		if (this->getStateCurr() == cSpaceshipIdle)
		{
			Collider* behaviorCollider = this->Parent()->Has(Collider);
			if (behaviorCollider)
			{
				//ColliderSetCollisionHandler(behaviorCollider, BehaviorSpaceshipCollisionHandler);
			}
		}
		if (this->getStateCurr() == cSpaceshipThrust)
		{
			this->setTimer(spaceshipDeathDuration);
		}
	}
}
 void BehaviorSpaceship::onUpdate( float dt)
{
	switch (this->getStateCurr())
	{
	  case cSpaceshipIdle:
	  {
		  this->BehaviorSpaceshipUpdateRotation(dt);
		  this->BehaviorSpaceshipUpdateWeapon(dt);
		  if (DGL_Input_KeyDown(VK_UP))
		  {
			  this->setStateNext(BehaviorSpaceship::cSpaceshipThrust);
		  }
		  break;
	  }
		  
	  case cSpaceshipThrust:
	  {
		  this->BehaviorSpaceshipUpdateRotation(dt);
		  this->BehaviorSpaceshipUpdateVelocity(dt);
		  this->BehaviorSpaceshipUpdateWeapon(dt);
		  if (!DGL_Input_KeyDown(VK_UP))
		  {
			  this->setStateNext(BehaviorSpaceship::cSpaceshipIdle);
		  }
		  break;
	  }  
	  case cSpaceshipDead: 
	  {
		  float setTime = this->getTimer();
		  setTime -= dt;
		  this->setTimer(setTime);
		  if (this->getTimer() < 0)
		  {
			  SceneRestart();
		  }
		  else
		  {
			  Transform* parentTransform = this->Parent()->Has(Transform);
			  Sprite* parentSprite = this->Parent()->Has(Sprite);
			  if (parentTransform && parentSprite)
			  {
				  float parentAlpha = parentSprite->SpriteGetAlpha();
				  Vector2D scale = *parentTransform->TransformGetScale();
				  float rotation = parentTransform->TransformGetRotation();
				  scale.x += 90 * dt;
				  scale.y += 130 * dt;	
				  rotation += 10 * dt;

				  parentTransform->TransformSetScale(&scale);
				  parentTransform->TransformSetRotation(rotation);
				  setTime -= dt;
				  this->setTimer(setTime);
				  parentSprite->SpriteSetAlpha(parentAlpha -= dt);

			  }
		  }
	  }
	}

	TeleporterUpdateEntity(this->Parent());
}
 void BehaviorSpaceship::onExit()
{
	
}
 void BehaviorSpaceship::BehaviorSpaceshipUpdateRotation(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (this)
	{
		Physics* physicsComponent =  this->Parent()->Has(Physics);
		float rotationVelocity = physicsComponent->PhysicsGetRotationalVelocity();

		if (DGL_Input_KeyDown(VK_LEFT))
		{
			rotationVelocity = spaceshipTurnRateMax;
			physicsComponent->PhysicsSetRotationalVelocity(rotationVelocity);
		}
		else if (DGL_Input_KeyDown(VK_RIGHT))
		{
			rotationVelocity = -spaceshipTurnRateMax;
			physicsComponent->PhysicsSetRotationalVelocity(rotationVelocity);
		}
		else
		{
			physicsComponent->PhysicsSetRotationalVelocity(0);
		}
	}
}
 void BehaviorSpaceship::BehaviorSpaceshipUpdateVelocity(float dt)
{
	if (this)
	{
		Physics* physcicsComponenet = this->Parent()->Has(Physics);
		Transform* transformComponent =  this->Parent()->Has(Transform);
		if (physcicsComponenet && transformComponent)
		{ 
			float speed;
			float scalar = spaceshipAcceleration * dt;
			float rotation = transformComponent->TransformGetRotation();
			Vector2D velocity = *physcicsComponenet->PhysicsGetVelocity();
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
			physcicsComponenet->PhysicsSetVelocity(&velocity);
		}

	}
}
void BehaviorSpaceship::BehaviorSpaceshipUpdateWeapon(float dt)
{
	if (this->getTimer() > 0)
	{
		float time = this->getTimer();
		time -= dt;
		this->setTimer(time);
		if (this->getTimer() < 0)
		{
			this->setTimer(0);
		}
    }
	if (DGL_Input_KeyDown(VK_SPACE))
	{
		if (this->getTimer() <= 0)
		{
		
			this->BehaviorSpaceshipSpawnBullet();
			this->setTimer(spaceshipWeaponCooldownTime);
		}
	}
}
void BehaviorSpaceship::BehaviorSpaceshipSpawnBullet()
{
	Entity *bullet = NULL;

	
 	bullet = EntityFactoryBuild("Bullet");
	if (bullet)
	{

		Transform* SpaceShiptransformComponent = this->Parent()->Has(Transform);
		Physics* physicsComponentBullet = bullet->Has(Physics);
		if (SpaceShiptransformComponent && physicsComponentBullet)
		{
			Vector2D SpaceShipPosition = *SpaceShiptransformComponent->TransformGetTranslation();
			float SpaceShipRotation = SpaceShiptransformComponent->TransformGetRotation();
			Transform* bulletTransformComponent = bullet->Has(Transform);
			Vector2D bulletPosition = SpaceShipPosition;
			Vector2D bulletVelocity = *physicsComponentBullet->PhysicsGetVelocity();
			Vector2D nomarlizedDirection;
		    bulletTransformComponent->TransformSetRotation(SpaceShipRotation);
			Vector2DFromAngleRad(&nomarlizedDirection, SpaceShipRotation);
			Vector2DNormalize(&nomarlizedDirection, &nomarlizedDirection);
			Vector2DScale(&bulletVelocity, &nomarlizedDirection, spaceshipWeaponBulletSpeed);
	        physicsComponentBullet->PhysicsSetVelocity(&bulletVelocity);
            bulletTransformComponent->TransformSetTranslation(&bulletPosition);
			SceneAddEntity(bullet);

		}
		return;
		
	}
}

 void BehaviorSpaceship::BehaviorSpaceshipCollisionHandler(Entity* entity1, const Entity* entity2)
{
	if (entity1 && entity2)
	{
		if ((!strncmp(entity2->EntityGetName(), "Asteroid", _countof("Asteroid"))))
		{
			Behavior* entity1Behavior = entity1->Has(Behavior);
			if (entity1)
			{
				entity1Behavior->setStateNext(BehaviorSpaceship::cSpaceshipDead);
			}
		}
	}
}

 BehaviorSpaceship* BehaviorSpaceship::Clone() const
 {
	 return new BehaviorSpaceship(*this);
 }

