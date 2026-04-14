//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorBullet.h"
#include "Behavior.h"
#include "DGL.h"
#include "Entity.h"
#include "Teleporter.h"
#include "Collider.h"

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



//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
 void BehaviorBullet::onInit()
{
	if (this->getStateCurr() == cBulletIdle)
	{
		Collider* bulletCollider = this->Parent()->Has(Collider);
		if (bulletCollider)
		{
			//ColliderSetCollisionHandler(bulletCollider, BehaviorBulletCollisionHandler);
		}
	}
}
 void BehaviorBullet::onUpdate(float dt)
 {
	if (this)
	{
	switch(this->getStateCurr())
	{
	 case cBulletIdle:
		 BehaviorBulletUpdateLifeTimer(dt);
		 break;
	}
	TeleporterUpdateEntity(this->Parent());
 }
}
void BehaviorBullet::BehaviorBulletUpdateLifeTimer(float dt)
{
	if(this)
	{
		if (this->getTimer() > 0)
		{
			float timer_ = this->getTimer();
			timer_ -= dt;
			this->setTimer(timer_);
			if (this->getTimer() <= 0)
			{
				this->Parent()->EntityDestroy();
			}
		}

	}	
}

void BehaviorBullet::BehaviorBulletCollisionHandler(Entity* entity1, const Entity* entity2)
{
	if (entity1 && entity2)
	{
		if ((!strncmp(entity2->EntityGetName(), "Asteroid", _countof("Asteroid"))))
		{
			entity1->EntityDestroy();
		}
	}
}

BehaviorBullet* BehaviorBullet::Clone() const
{
	return new BehaviorBullet(*this);
}


