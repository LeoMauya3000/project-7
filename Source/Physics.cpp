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

Physics* Physics::Clone() const
{
	return new Physics(*this);
}

void Physics::PhysicsRead(Stream stream)
{

	if (stream)
	{
		StreamReadVector2D(stream, &this->acceleration);
		StreamReadVector2D(stream, &this->velocity);
	}
} 
const Vector2D* Physics::PhysicsGetAcceleration() const
{
	return &this->acceleration;
}
const Vector2D* Physics::PhysicsGetVelocity()const
{
	return &this->velocity;
}
const Vector2D* Physics::PhysicsGetOldTranslation() const
{
	return &this->oldTranslation;
	
}
void Physics::PhysicsSetAcceleration(const Vector2D* acceleration)
{
	this->acceleration = *acceleration;
}
void Physics::PhysicsSetVelocity( const Vector2D* velocity)
{
	this->velocity = *velocity; 
}
void Physics::Update(float dt)
{

	if (this->Parent()->Has(Transform))
	{

	    float rotationVelocity = this->Parent()->Has(Physics)->PhysicsGetRotationalVelocity();
		float transformRotaion = this->Parent()->Has(Transform)->TransformGetRotation();
		const Vector2D* translationPtr = this->Parent()->Has(Transform)->TransformGetTranslation();
		Vector2D translation = *translationPtr;
		this->oldTranslation = *translationPtr;
		Vector2DScaleAdd(&this->velocity, &this->acceleration, dt, &this->velocity);
		Vector2DScaleAdd(&translation, &this->velocity, dt, &translation);
		this->Parent()->Has(Transform)->TransformSetTranslation(&translation);
		transformRotaion += rotationVelocity * dt;	
		this->Parent()->Has(Transform)->TransformSetRotation(transformRotaion);
	}
}
Physics* Physics::Clone()const
{
	return new Physics(*this);
}

float Physics::PhysicsGetRotationalVelocity() const
{
	this->rotationalVelocity;
}
void Physics::PhysicsSetRotationalVelocity(float rotationalVelocity)
{
		this->rotationalVelocity = rotationalVelocity;
}

void Physics::PhysicsSetDrag(float drag)
{
	this->drag = drag;
}