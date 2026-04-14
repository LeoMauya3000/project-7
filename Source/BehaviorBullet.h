//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Behavior.h"
//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------
class BehaviorBullet : public Behavior
{

	enum  state
	{
		cBulletInvalid = -1,
		cBulletIdle
	};
public:
	BehaviorBullet(Stream _stream)
	{
		this->BehaviorRead(_stream);
	}
	void onInit() override;
	void onUpdate(float dt) override;
	void onExit() override {};
	BehaviorBullet* Clone() const override;


private:
	
	void BehaviorBulletUpdateLifeTimer(float dt);
	void BehaviorBulletCollisionHandler(Entity* entity1, const Entity* entity2);

};