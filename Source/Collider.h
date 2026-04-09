//------------------------------------------------------------------------------
//
// File Name:	Collider.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 6
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Component.h"
//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------


class  Entity;
typedef FILE* Stream;

class Collider : public Component
{
	typedef void(*CollisionEventHandler)(Entity* entity1, const Entity* entity2);


   public:

	enum ColliderType
	{
		ColliderTypeNone,
		ColliderTypeCircle,
		ColliderTypeLine,
		DEFAULT

	};
	   Collider() : Component(Component::cCollider),colliderType(DEFAULT),handler(NULL),memorySize(0){};
	   ~Collider() {};
	   Collider(ColliderType type_) : colliderType(type_), handler(NULL), memorySize(0){}
	   Collider* Clone() const override;
	   void ColliderSetCollisionHandler(CollisionEventHandler handler);
	   Collider::ColliderType ReturnColliderType() const { return colliderType; } 
	   CollisionEventHandler ReturnHandler() const { return handler; }


    private:

	ColliderType colliderType;

	CollisionEventHandler	handler;

	unsigned int	memorySize;

};



//------------------------------------------------------------------------------


