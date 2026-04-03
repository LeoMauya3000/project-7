//------------------------------------------------------------------------------
//
// File Name:	Collider.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Collider.h"
#include "Entity.h"
#include "Transform.h"
#include "DGL.h"
#include "Vector2D.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"

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
bool ColliderIsColliding(const Collider* collider, const Collider* other);
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...


//Collider* ColliderCreate(void)
//{
//	Collider* collider = (Collider*)calloc(1, sizeof(Collider));
//	if (collider)
//	{
//		return collider;
//	}
//	return NULL;
//}
Collider* ColliderClone(const Collider* other)
{
	if (other)
	{

		Collider* collider = (Collider*)calloc(1, other->memorySize);
		if (collider)
		{
			memcpy(collider, other, other->memorySize);
			collider->parent = NULL;
			return collider;
		}
	}
	return NULL;
	
}
void ColliderFree(Collider** collider)
{
	if (*collider && collider)
	{
		free(*collider);
		*collider = NULL;
	}
}

//void ColliderRead(Collider* collider, Stream stream)
//{
//
//	collider;
//	stream;
//}
void ColliderSetParent(Collider* collider, Entity* parent)
{
	if (collider && parent)
	{
		collider->parent = parent;
	}

	return;
}

void ColliderCheck(const Collider* collider, const Collider* other)
{
	if (collider && other)
	{
		/*float radiusA = (TransformGetScale(EntityGetTransform(collider->parent))->x / 2.0f);
		float radiusB = (TransformGetScale(EntityGetTransform(other->parent))->x / 2.0f);
		Vector2D positionA = *TransformGetTranslation(EntityGetTransform(collider->parent));
		Vector2D positionB = *TransformGetTranslation(EntityGetTransform(other->parent));
		float radiusSum = radiusA + radiusB;
		if(Vector2DSquareDistance(&positionA,&positionB) <= radiusSum * radiusSum)*/
		if (ColliderIsColliding(collider, other))
		{
			if (collider->handler)
			{
				collider->handler(collider->parent, other->parent);
			}
			if (other->handler)
			{
				other->handler(other->parent, collider->parent);
			}
		}
	}
}
void ColliderSetCollisionHandler(Collider* collider, CollisionEventHandler handler)
{
	if (!collider)
	{
		return;
	}
     
	collider->handler = handler;
	if (!collider->handler)
	{
		collider->handler = NULL;
	}
}

bool ColliderIsColliding(const Collider* collider, const Collider* other)
{
	if (collider && other)
	{
		if (collider->type == ColliderTypeCircle && other->type == ColliderTypeCircle)
		{
			//local variable for test sake dattebayo!
			bool returnValue = ColliderCircleIsCollidingWithCircle(collider, other);
			return returnValue;
		}
		if ((collider->type == ColliderTypeCircle && other->type == ColliderTypeLine )|| (collider->type == ColliderTypeLine && other->type == ColliderTypeCircle))
		{
			bool returnvValue = ColliderLineIsCollidingWithCircle(collider, other);
			return returnvValue;
		}
		if (collider->type == ColliderTypeLine && other->type == ColliderTypeLine)
		{
			return false;
		}
	
		return false;
	}
	else
	{
		return false;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

