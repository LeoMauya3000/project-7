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

Behavior* Behavior::Clone() const
{
	return new Behavior(*this);
}
void Behavior::BehaviorRead(Stream stream)
{
	if (stream)
	{
		int _stateCurr = StreamReadInt(stream);
		int _stateNext = StreamReadInt(stream);
		float _timerValue = StreamReadFloat(stream);
		this->stateCurr = _stateCurr;
		this->stateNext = _stateNext;
		this->timer = _timerValue;
	}
}
void Behavior::Update(float dt)
{

	if (this)
	{
		if (this->stateCurr != this->stateNext)
		{
			if (this->onExit)
			{
				this->onExit(this);
			}
			this->stateCurr = this->stateNext;

		    if (this->onInit)
			{
				this->onInit(this);
			}

		}

		if (this->onUpdate)
		{
			this->onUpdate(this, dt);
		}
	}
}

