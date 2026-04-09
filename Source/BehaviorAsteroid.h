//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteroid.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Behavior Behavior;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

// An example of the enum to be defined in BehaviorAsteroid.c.



class BehaviorAsteroid : public Behavior
{

	enum
	{
		cAsteroidOriginTlc,
		cAsteroidOriginTrc,
		cAsteroidOriginBlc,
		cAsteroidOriginBrc,
		cAsteroidOriginCount,

	};
public :
	

	void BehaviorAsteroidInit();

	void BehaviorAsteroidUpdate( float dt);
	
	void BehaviorAsteroidSetPosition(BehaviorAsteroid* behavior);
	void BehaviorAsteroidSetVelocity(BehaviorAsteroid* behavior);
	
	static void BehaviorAsteroidCollisionHandler(Entity* obj1, const Entity* obj2);


private:

	Behavior	base;
	AsteroidOrigin	origin;

};


