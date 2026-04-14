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
#include "Behavior.h"

class Entity;
class Component;
class BehaviorAsteroid : public Behavior
{
	 enum asteriodStates
	{
		cAsteroidInvalid = -1,
		cAsteroidIdle = 0,
	};


public :
	
	enum AsteroidOrigin
	{
		cAsteroidOriginTlc,
		cAsteroidOriginTrc,
		cAsteroidOriginBlc,
		cAsteroidOriginBrc,
		cAsteroidOriginCount,

	};

	BehaviorAsteroid(Stream _stream)
	{
		this->BehaviorRead(_stream);
		origin = (AsteroidOrigin)0;
	}
	void  onUpdate(float dt) override;

	void  onInit() override;

	void  onExit() override {}; 

	BehaviorAsteroid* Clone() const override;


private:
	void BehaviorAsteroidSetPosition();
	void BehaviorAsteroidSetVelocity();
	void BehaviorAsteroidCollisionHandler(Entity* obj1, const Entity* obj2);
	AsteroidOrigin	origin;

};


