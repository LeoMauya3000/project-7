//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Behavior.h"

class BehaviorSpaceship : public Behavior
{
public:



	enum  state
	{
		cSpaceshipInvalid = -1,
		cSpaceshipIdle,
		cSpaceshipThrust,
		cSpaceshipDead

	};
    
	BehaviorSpaceship(Stream _stream)
	{
		this->BehaviorRead(_stream);
	}
	void onInit() override;
	void onUpdate(float dt) override;
	void onExit() override;

	BehaviorSpaceship* Clone() const override;



private:

	 void BehaviorSpaceshipUpdateRotation(float dt);
	 void BehaviorSpaceshipUpdateVelocity( float dt);
	 void BehaviorSpaceshipUpdateWeapon(float dt);
	 void BehaviorSpaceshipSpawnBullet();
	 void BehaviorSpaceshipCollisionHandler(Entity* entity1, const Entity* entity2);
};

//------------------------------------------------------------------------------
