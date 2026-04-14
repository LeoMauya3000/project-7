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
	};
	   Collider() : Component(Component::cCollider),handler(NULL){};
	   virtual ~Collider() = 0 {};
	   Collider(ColliderType type_) : colliderType(type_), handler(NULL), Component(Component::cCollider) {};
	   virtual Collider* Clone() const = 0;
	 
	   ColliderType ReturnColliderType() const { return colliderType; } 
	   CollisionEventHandler ReturnHandler() const { return handler; }
	   void ColliderSetCollisionHandler(CollisionEventHandler handler);
	   void ColliderCheck(const Collider* collider, const Collider* other);
	   bool ColliderIsColliding(const Collider* collider, const Collider* other);

    private:
		 
	ColliderType colliderType;

	CollisionEventHandler	handler;


};



//------------------------------------------------------------------------------


