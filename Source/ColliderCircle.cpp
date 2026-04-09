//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ColliderCircle.h"
#include "Collider.h"
#include "Stream.h"
#include "transform.h"
#include "Physics.h"	
#include "DGL.h"
#include "Vector2D.h"
#include "Entity.h"
typedef struct ColliderCircle
{
	// Inherit the base collider structure.
	Collider	base;

	// Radius of the circle collider.
	float radius;

} ColliderCircle;

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
Collider* ColliderCircleCreate(void)
{
	ColliderCircle* circleCollider = calloc(1, sizeof(ColliderCircle));
	if (circleCollider)
	{
		circleCollider->base.memorySize = sizeof(ColliderCircle);
		circleCollider->base.type = ColliderTypeCircle;
		circleCollider->radius = 0.5f;
		return (Collider*)circleCollider;
	}
	else
	{
		return NULL;
	}
}

void ColliderCircleRead(Collider* collider, Stream stream)
{
	if (collider && stream)
	{
		ColliderCircle* circleCollider = (ColliderCircle*)collider;
		float radius = StreamReadFloat(stream);
		circleCollider->radius = radius;

	}
}

float ColliderCircleGetRadius(const Collider* collider)
{
	if (collider)
	{
		ColliderCircle *circleCollider = (ColliderCircle*)collider;
		return circleCollider->radius;
	}
	else
	{
		return 0;
	}
}
void ColliderCircleSetRadius(Collider* collider, float radius)
{
	if (collider)
	{
		ColliderCircle* circleColldier = (ColliderCircle*)collider;
		circleColldier->radius = radius;
	}
}
bool ColliderCircleIsCollidingWithCircle(const Collider* collider, const Collider* other)
{
	if (collider && other)
	{
		float radiusA = (TransformGetScale(EntityGetTransform(collider->parent))->x / 2.0f);
		float radiusB = (TransformGetScale(EntityGetTransform(other->parent))->x / 2.0f);
		Vector2D positionA = *TransformGetTranslation(EntityGetTransform(collider->parent));
		Vector2D positionB = *TransformGetTranslation(EntityGetTransform(other->parent));
		float radiusSum = radiusA + radiusB;

		if (Vector2DSquareDistance(&positionA, &positionB) <= radiusSum * radiusSum)
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
void ColliderCircleInit()
{
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void ColliderCircleUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);
}

// Shutdown the ...
void ColliderCircleExit()
{
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

