//------------------------------------------------------------------------------
//
// File Name:	Physics.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Entity.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------


struct _iobuf;
typedef struct _iobuf FILE;
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in Physics.c.
class Transform;
class Entity;

class  Physics : public Component
{
  public:

	  Physics() :oldTranslation({ 0,0 }), acceleration({ 0,0 }), velocity({0,0}), rotationalVelocity(0),drag(0){};
	  ~Physics() {};

	  Physics* Clone() const override;

	  void PhysicsRead(Stream stream);

	  const Vector2D* PhysicsGetAcceleration()const;

	  const Vector2D* PhysicsGetVelocity()const;

	  float PhysicsGetRotationalVelocity()const;

	  const Vector2D* PhysicsGetOldTranslation() const;

	  void PhysicsSetAcceleration( const Vector2D* _acceleration);

	  void PhysicsSetVelocity(const Vector2D* _velocity);

	  void PhysicsSetRotationalVelocity( float rotationalVelocity);

	  void PhysicsSetDrag(float drag);

	  void Update(float dt) override;




   private:
	Vector2D	oldTranslation;
	Vector2D	acceleration;
	Vector2D	velocity;
	float rotationalVelocity;
	float drag;
};



//------------------------------------------------------------------------------

