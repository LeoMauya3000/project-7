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
#include "Behavior.h"
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

typedef enum asteriodStates
{
	cAsteroidInvalid = -1,
	cAsteroidIdle = 0,
}asteriodStates;

typedef enum
{
	cAsteroidOriginTlc,
	cAsteroidOriginTrc,
	cAsteroidOriginBlc,
	cAsteroidOriginBrc,
	cAsteroidOriginCount,

}AsteroidOrigin;

typedef struct BehaviorAsteroid
{
	// Inherit the base behavior structure.
	Behavior	base;

	// Add asteroid-specific behavior variables.
	AsteroidOrigin	origin;

} BehaviorAsteroid;

static void BehaviorAsteroidInit(Behavior* asteriodBehavior);
static void BehaviorAsteroidUpdate(Behavior* asteriodBehavior, float dt);
static void BehaviorAsteroidExit(Behavior* asteriodBehavior);
static void BehaviorAsteroidSetPosition(BehaviorAsteroid* behavior);
static void BehaviorAsteroidSetVelocity(BehaviorAsteroid* behavior);
static void BehaviorAsteroidCollisionHandler(Entity* obj1, const Entity* obj2);








// Initialize the ...


// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorAsteriodUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt); 
}

// Shutdown the ...
void BehaviorAsteriodExit()
{
}
Behavior* BehaviorAsteroidCreate(void)
{
	BehaviorAsteroid* asteriod = (BehaviorAsteroid*)calloc(1, sizeof(BehaviorAsteroid));
	if (asteriod)
	{
		asteriod->base.stateCurr = cAsteroidInvalid;
		asteriod->base.stateNext = cAsteroidInvalid;
		asteriod->base.memorySize = sizeof(BehaviorAsteroid);
		asteriod->base.onInit = &BehaviorAsteroidInit;
		asteriod->base.onUpdate = &BehaviorAsteroidUpdate;
		asteriod->base.onExit = &BehaviorAsteroidExit;
		return (Behavior*)asteriod;
	}

	return NULL;
}


 void BehaviorAsteroidInit(Behavior* asteriodBehavior)
{
	BehaviorAsteroid* behaviorAsteriod = (BehaviorAsteroid*)asteriodBehavior;

	if (asteriodBehavior->stateCurr == cAsteroidIdle)
	{
		
		behaviorAsteriod->origin = RandomRange(0, 3);
		BehaviorAsteroidSetPosition(behaviorAsteriod);
		BehaviorAsteroidSetVelocity(behaviorAsteriod);
		Collider* parentEntityCollider = EntityGetCollider(asteriodBehavior->parent);
		if (parentEntityCollider)
		{
			ColliderSetCollisionHandler(parentEntityCollider, BehaviorAsteroidCollisionHandler);
		}
		
	}

}
 void BehaviorAsteroidUpdate(Behavior* asteriodBehavior, float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (asteriodBehavior)
	{
		// okay whats actually gotta go here lmao 
		/*switch (asteriodBehavior->stateCurr)
		{
		  case cAsteroidIdle:
		  {
			  BehaviorAsteroidSetPosition((BehaviorAsteroid*)asteriodBehavior);
			  BehaviorAsteroidSetVelocity((BehaviorAsteroid*)asteriodBehavior);
			  break;
		  }
		  default:
		  {
			  break;
		  }
		}*/
	 TeleporterUpdateEntity(asteriodBehavior->parent);
	}
}
 void BehaviorAsteroidExit(Behavior* asteriodBehavior)
{
	UNREFERENCED_PARAMETER(asteriodBehavior);
}
 void BehaviorAsteroidSetPosition(BehaviorAsteroid* behavior)
{
	Vector2D screenSize = DGL_Window_GetSize();
	Vector2D halfSize;
	Vector2DScale(&halfSize, &screenSize, 0.5f);
	if (behavior)
	{
		Transform* entityTransform = EntityGetTransform(behavior->base.parent);
		if (entityTransform)
		{
			switch (behavior->origin)
			{
			    case cAsteroidOriginTlc:
			    {
				 TransformSetTranslation(entityTransform, &(Vector2D) { -halfSize.x, halfSize.y });
				 break;
			    }
				case cAsteroidOriginTrc:
				{
				 TransformSetTranslation(entityTransform, &(Vector2D){halfSize.x, halfSize.y});
				 break;
				}
				case cAsteroidOriginBlc:
				{
				TransformSetTranslation(entityTransform, &(Vector2D){-halfSize.x, -halfSize.y});
				break;
				}
				case cAsteroidOriginBrc:
				{
				TransformSetTranslation(entityTransform, &(Vector2D){halfSize.x, -halfSize.y});
				break;
				}
				default:
				{
					TransformSetTranslation(entityTransform, &(Vector2D){0,0});
					break;
				}
			}
		}
	}
}
 void BehaviorAsteroidSetVelocity(BehaviorAsteroid* behavior)
{
	if (behavior)
	{
		float angle;
		Vector2D velocity;
		Physics* entityPhysics = EntityGetPhysics(behavior->base.parent);
		if (entityPhysics)
		{
			float asteriodSpeed;
			float randomSpeed = RandomRangeFloat(asteroidSpeedMin, asteroidSpeedMax);
			switch (behavior->origin)
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
			PhysicsSetVelocity(entityPhysics,&velocity);
		}
	}
}
static void BehaviorAsteroidCollisionHandler(Entity* obj1, const Entity* obj2)
{
	if (obj1 && obj2)
	{
		if ((!strncmp(EntityGetName(obj2), "Bullet", _countof("Bullet"))) || ((!strncmp(EntityGetName(obj2), "SpaceShip", _countof("SpaceShip")))))
		{ 
			ScoreSystemIncreaseScore(20); 
			EntityDestroy(obj1);
		}
	}
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

