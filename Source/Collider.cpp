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
#include "Component.h"



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
//void ColliderRead(Collider* collider, Stream stream)
//{
//
//	collider;
//	stream;
//}
//void Collider::ColliderCheck(const Collider* collider, const Collider* other)
//{
//	/*if (collider && other)
//	{
//		if (ColliderIsColliding(collider, other))
//		{
//			if (collider->ReturnHandler())
//			{
//				collider->ReturnHandler()(collider->Parent(), other->Parent());
//			}
//			if (other->ReturnHandler())
//			{
//				other->ReturnHandler()(other->Parent(), collider->Parent());
//			}
//		}
//	}*/
//}

Collider* Collider::Clone()const
{
	return new Collider(*this);
}

void Collider::ColliderSetCollisionHandler(CollisionEventHandler _handler)
{
	this->handler = _handler;
}

bool ColliderIsColliding(const Collider* collider, const Collider* other)
{
	if (collider && other)
	{
		if (collider->ReturnColliderType() == Collider::ColliderTypeCircle && other->ReturnColliderType() == Collider::ColliderTypeCircle)
		{
			//local variable for test sake dattebayo!
			/*bool returnValue = ColliderCircleIsCollidingWithCircle(collider, other);
			return returnValue;*/
		}
		if ((collider->ReturnColliderType() == Collider::ColliderTypeCircle && other->ReturnColliderType() == Collider::ColliderTypeLine) || (collider->ReturnColliderType() == Collider::ColliderTypeLine && other->ReturnColliderType() == Collider::ColliderTypeCircle))
		{
			/*bool returnvValue = ColliderLineIsCollidingWithCircle(collider, other);
			return returnvValue;*/
		}
		if (collider->ReturnColliderType() == Collider::ColliderTypeLine && other->ReturnColliderType() == Collider::ColliderTypeLine)
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

