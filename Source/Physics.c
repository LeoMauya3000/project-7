//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Physics.h"
#include "DGL.h"
#include "Stream.h"
#include "Vector2D.h"
#include "Transform.h"


//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Physics
{
	// Previous position.  May be used for resolving collisions.
	Vector2D	oldTranslation;

	// Acceleration = inverseMass * (sum of forces)
	Vector2D	acceleration;

	// Velocity may be stored as a direction vector and speed scalar, instead.
	Vector2D	velocity;

	// Rotational velocity (in radians).
	float rotationalVelocity;

	// Used when calculating acceleration due to forces.
	// Used when resolving collision between two dynamic objects.
	//float		inverseMass;

} Physics;


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


Physics* PhysicsCreate(void)
{
	Physics* physics = calloc(1, sizeof(Physics));
	if (physics)
	{
		return physics;
	}
	else
	{
		return NULL;
	}
	
	
}
void PhysicsFree(Physics** physics)
{
	free(*physics);
	*physics = NULL;
}
void PhysicsRead(Physics* physics, Stream stream)
{

	if (stream)
	{
		StreamReadVector2D(stream, &physics->acceleration);
		StreamReadVector2D(stream, &physics->velocity);
	}
	

} 
const Vector2D* PhysicsGetAcceleration(const Physics* physics)
{

	if (physics)
	{
		return &physics->acceleration;
	}
	else
	{
		return NULL;
	}
	
}
const Vector2D* PhysicsGetVelocity(const Physics* physics)
{
	if (physics)
	{
		return &physics->velocity;
	}
	else
	{
		return NULL;
	}

}
const Vector2D* PhysicsGetOldTranslation(const Physics* physics)
{
	if (physics)
	{
		return &physics->oldTranslation;
	}
	else
	{
		return NULL;
	}
	
}
void PhysicsSetAcceleration(Physics* physics, const Vector2D* acceleration)
{
	physics->acceleration = *acceleration;
	
}
void PhysicsSetVelocity(Physics* physics, const Vector2D* velocity)
{
	physics->velocity = *velocity; 
}
void PhysicsUpdate(Physics* physics, Transform* transform, float dt)
{

	if (physics != NULL && transform != NULL)
	{

	    float rotationVelocity = PhysicsGetRotationalVelocity(physics);
		float transformRotaion = TransformGetRotation(transform);
		const Vector2D* translationPtr = TransformGetTranslation(transform);
		Vector2D translation = *translationPtr;
		physics->oldTranslation = *translationPtr;
		Vector2DScaleAdd(&physics->velocity, &physics->acceleration, dt, &physics->velocity);
		Vector2DScaleAdd(&translation, &physics->velocity, dt, &translation);
		TransformSetTranslation(transform, &translation);
		transformRotaion += rotationVelocity * dt;	
		TransformSetRotation(transform, transformRotaion);
		


	}
}
Physics* PhysicsClone(const Physics* other)
{
	if (other)
	{
		Physics* clonePhyscics = calloc(1, sizeof(Physics));
		if (clonePhyscics)
		{
			*clonePhyscics = *other;
			return clonePhyscics;
		}
	}
	return NULL;
}

float PhysicsGetRotationalVelocity(const Physics* physics)
{
	if (physics)
	{
		return physics->rotationalVelocity;
	}
	return 0;
}
void PhysicsSetRotationalVelocity(Physics* physics, float rotationalVelocity)
{
	if (physics)
	{
		physics->rotationalVelocity = rotationalVelocity;
	}
}