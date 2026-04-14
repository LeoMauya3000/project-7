//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteriod.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorAsteroid.h"
#include "Random.h"
#include  "Collider.h"
#include "Entity.h"
#include "Teleporter.h"
#include "ScoreSystem.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Physics.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const float asteroidSpeedMin = 50.0f;
static const float asteroidSpeedMax = 100.0f;


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
 void BehaviorAsteroid::onInit()
{
	if (this->getStateCurr() == cAsteroidIdle)
	{
		
		this->origin = (AsteroidOrigin)RandomRange(0, 3);
		this->BehaviorAsteroidSetPosition();
		this->BehaviorAsteroidSetVelocity();
		Collider* parentEntityCollider = this->Parent()->Has(Collider);
		if (parentEntityCollider)
		{
		/*	parentEntityCollider->ColliderSetCollisionHandler(BehaviorAsteroidCollisionHandler);*/
		}
		
	}

}
 void BehaviorAsteroid::onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (this)
	{
	 TeleporterUpdateEntity(Parent());
	}
}
 void BehaviorAsteroid::BehaviorAsteroidSetPosition()
{
	Vector2D screenSize = DGL_Window_GetSize();
	Vector2D halfSize;
	Vector2DScale(&halfSize, &screenSize, 0.5f);
	if (this)
	{
		Transform* entityTransform = this->Parent()->Has(Transform);
		if (entityTransform)
		{
			switch (this->origin)
			{
			    case cAsteroidOriginTlc:
			    {
				 Vector2D corner = { -halfSize.x, halfSize.y };
				 entityTransform->TransformSetTranslation(&corner);
				 break;
			    }
				case cAsteroidOriginTrc:
				{
					Vector2D corner = { halfSize.x , halfSize.y };
					entityTransform->TransformSetTranslation(&corner);
				 break;
				}
				case cAsteroidOriginBlc:
				{
					Vector2D corner = { -halfSize.x, -halfSize.y };
			     	entityTransform->TransformSetTranslation(&corner);
				break;
				}
				case cAsteroidOriginBrc:
				{
					Vector2D corner = { halfSize.x, -halfSize.y };
					entityTransform->TransformSetTranslation(&corner);
				break;
				}
				default:
				{
					DGL_Vec2 zeroVec = { 0,0 };
					entityTransform->TransformSetTranslation(&zeroVec);
					break;
				}
			}
		}
	}
}
 void BehaviorAsteroid::BehaviorAsteroidSetVelocity()
{
	if (this)
	{
		float angle;
		Vector2D velocity;
		Physics* entityPhysics = this->Parent()->Has(Physics);
		if (entityPhysics)
		{
			float asteriodSpeed;
			float randomSpeed = RandomRangeFloat(asteroidSpeedMin, asteroidSpeedMax);
			switch (this->origin)
			{
			 case cAsteroidOriginTlc:
			 {
				angle = RandomRangeFloat(-10, -80);
				break;
			 }
			 case cAsteroidOriginTrc:
			 {
				angle = RandomRangeFloat(-100, -170);
				break;
			 }
			 case cAsteroidOriginBlc:
			 {
				angle = RandomRangeFloat(10, 80);
				break;
			 }
			 case cAsteroidOriginBrc:
			 {
				angle = RandomRangeFloat(100, 170);
				break;
			 }
			 default:
			 {
				 angle = 0;
				 break;
			 }
			}

			Vector2DFromAngleDeg(&velocity, angle);
			asteriodSpeed = Vector2DLength(&velocity);
			asteriodSpeed *= randomSpeed;
			Vector2DScale(&velocity, &velocity, asteriodSpeed);
			entityPhysics->PhysicsSetVelocity(&velocity);
		}
	}
}
void BehaviorAsteroid::BehaviorAsteroidCollisionHandler(Entity* obj1, const Entity* obj2)
{
	if (obj1 && obj2)
	{
		if ((!strncmp(obj2->EntityGetName(), "Bullet", _countof("Bullet"))) || ((!strncmp(obj2->EntityGetName(), "SpaceShip", _countof("SpaceShip")))))
		{ 
			ScoreSystemIncreaseScore(20); 
			obj1->EntityDestroy();
		}
	}
}

BehaviorAsteroid* BehaviorAsteroid::Clone() const
{
	return new BehaviorAsteroid(*this);
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

