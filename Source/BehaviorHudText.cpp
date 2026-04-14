//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorHudText.h"
#include "Behavior.h"
#include "ScoreSystem.h"
#include "Entity.h"
#include "Sprite.h"
#include "stream.h"



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




// Initialize the ...
 void BehaviorHudText::onInit()
{
	if (this)
	{
		this->BehaviorHudTextUpdateText();
		this->Parent()->Has(Sprite)->SpriteSetText(this->displayString);
	}
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
 void BehaviorHudText::onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
		if (this)
		{
			unsigned int behaviorHudScore = ScoreSystemGetValue(this->scoreSystemId);
			if (this->displayValue != behaviorHudScore)
			{
				this->BehaviorHudTextUpdateText();
			}
		}
}

// Shutdown the ...
void BehaviorHudText::BehaviorHudTextRead( Stream stream)
{
	if (stream)
	{
		this->BehaviorRead( stream);
		strcpy_s(this->formatString, _countof(this->formatString), StreamReadToken(stream));
		this->scoreSystemId = (ScoreSystemId)StreamReadInt(stream);
		
	}
}
	
 void BehaviorHudText::BehaviorHudTextUpdateText()
{
	if (this)
	{
		if (this->scoreSystemId != SsiInvalid)
		{
			this->displayValue = ScoreSystemGetValue(this->scoreSystemId);
			sprintf_s(this->displayString, _countof(this->displayString), this->formatString, this->displayValue);
		}
	}
}



 BehaviorHudText* BehaviorHudText::Clone() const
 {
	 return new BehaviorHudText(*this);
 }
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

