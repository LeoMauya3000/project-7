//------------------------------------------------------------------------------
//
// File Name:	Behavior.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Behavior.h"
#include "Stream.h"

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

Behavior* BehaviorClone(const Behavior* other)
{
	if (other)
	{
		Behavior* clone = (Behavior*)calloc(1, other->memorySize);
		if (clone)
		{
			if (clone)
			{
			 memcpy(clone,other,other->memorySize);
		     return clone;
			}
		}
	}
	return NULL;
}
void BehaviorFree(Behavior** behavior)
{
	if (*behavior)
	{
		
 		free(*behavior);
		*behavior = NULL;
	}
}
void BehaviorRead(Behavior* behavior, Stream stream)
{
	if (stream && behavior)
	{
		int _stateCurr = StreamReadInt(stream);
		int _stateNext = StreamReadInt(stream);
		float _timerValue = StreamReadFloat(stream);
		behavior->stateCurr = _stateCurr;
		behavior->stateNext = _stateNext;
		behavior->timer = _timerValue;
	}
}
void BehaviorSetParent(Behavior* behavior, Entity* parent)
{
	if (behavior && parent)
	{
		behavior->parent = parent;
	}
}
void BehaviorUpdate(Behavior* behavior, float dt)
{

	if (behavior)
	{
		if (behavior->stateCurr != behavior->stateNext)
		{
			if (behavior->onExit)
			{
				behavior->onExit(behavior);
			}
			behavior->stateCurr = behavior->stateNext;

		    if (behavior->onInit)
			{
				behavior->onInit(behavior);
			}

		}

		if (behavior->onUpdate)
		{
           behavior->onUpdate(behavior, dt);
		}
	}
}

