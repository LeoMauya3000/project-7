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


void ColliderCircle::ColliderCircleRead(Stream stream)
{
	if (this && stream)
	{
		float _radius = StreamReadFloat(stream);
		this->radius = _radius;
	}
}

float ColliderCircle::ColliderCircleGetRadius()
{
	if (this)
	{
		return this->radius;
	}
	else
	{
		return 0;
	}
}
void ColliderCircle::ColliderCircleSetRadius(float _radius)
{
	if (this)
	{
		this->radius = _radius;
	}
}
bool ColliderCircle:: ColliderCircleIsCollidingWithCircle(const Collider* collider, const Collider* other)
{
	if (collider && other)
	{
	
		float radiusA = (collider->Parent()->Has(Transform)->TransformGetScale()->x / 2.0f);
		float radiusB = (other->Parent()->Has(Transform)->TransformGetScale()->x / 2.0f);
		Vector2D positionA = *collider->Parent()->Has(Transform)->TransformGetTranslation();
		Vector2D positionB = *other->Parent()->Has(Transform)->TransformGetTranslation();
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

ColliderCircle* ColliderCircle::Clone() const
{
	return new ColliderCircle(*this);
}
