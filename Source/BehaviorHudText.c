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

typedef enum HudTextStates
{
	cHudTextInvalid = -1,	// HUD Text has not yet been initialized.
	cHudTextIdle,			// HUD Text will normally remain static.

} HudTextStates;
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct BehaviorHudText
{
	// Inherit the base behavior structure.
	Behavior	base;

	// Add HUD Text-specific behavior variables.

	// The index used to access values from the Score System.
	ScoreSystemId scoreSystemId;

	// The format string to be used with sprintf_s() when updating the HUD Text object.
	// (For example: "Score: %d")
	// (NOTE: This buffer has an arbitrary length of 32 chars, which is sufficient for this project.
	//	Exercise caution when using buffers of a fixed length (e.g. use sprintf_s).
	char formatString[32];

	// The buffer to be used with sprintf_s() when updating the HUD Text object.
	// (For example: "Score: 9001")
	// (NOTE: This buffer has an arbitrary length of 32 chars, which is sufficient for this project.
	//	Exercise caution when using buffers of a fixed length (e.g. use sprintf_s).
	char displayString[32];

	// The value currently being displayed by the HUD Text object.
	// (NOTE: This value can be compared with *watchValue to determine when the text must be updated.)
	// (NOTE: Make sure to update this value each time the text is updated.)
	unsigned displayValue;

} BehaviorHudText;
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
static void BehaviorHudTextInit(Behavior* behvaior);
static void BehaviorHudTextUpdate(Behavior* behavior, float dt);
static void BehaviorHudTextExit(Behavior* behavior);
static void BehaviorHudTextUpdateText(BehaviorHudText* behvaiorText);



// Initialize the ...
static void BehaviorHudTextInit(Behavior* behvaior)
{
	if (behvaior)
	{

		BehaviorHudText* behaviorHudtext = (BehaviorHudText*)behvaior;
		BehaviorHudTextUpdateText(behaviorHudtext);
		SpriteSetText(EntityGetSprite(behaviorHudtext->base.parent), behaviorHudtext->displayString);
	}
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void BehaviorHudTextUpdate(Behavior* behavior, float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (behavior)
	{
		BehaviorHudText* behaviorHudtext = (BehaviorHudText*)behavior;
		if (behaviorHudtext)
		{
			unsigned int behaviorHudScore = ScoreSystemGetValue(behaviorHudtext->scoreSystemId);
			if (behaviorHudtext->displayValue != behaviorHudScore)
			{
				BehaviorHudTextUpdateText(behaviorHudtext);
			}
		}
	}
}

// Shutdown the ...
static void BehaviorHudTextExit(Behavior* behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}

Behavior* BehaviorHudTextCreate(void)
{
	BehaviorHudText* behaviorHudText = (BehaviorHudText*)calloc(1, sizeof(BehaviorHudText));
	if (behaviorHudText)
	{
		behaviorHudText->base.memorySize = sizeof(BehaviorHudText);
		behaviorHudText->base.stateCurr = cHudTextInvalid;
		behaviorHudText->base.stateCurr = cHudTextInvalid;
		behaviorHudText->base.onInit = &BehaviorHudTextInit;
		behaviorHudText->base.onUpdate = &BehaviorHudTextUpdate;
		behaviorHudText->base.onExit = &BehaviorHudTextExit;
		behaviorHudText->scoreSystemId = SsiInvalid;
		return (Behavior*)behaviorHudText;
	}
	else
	{
		return NULL;
	}
}

void BehaviorHudTextRead(Behavior* behavior, Stream stream)
{
	if (behavior && stream)
	{
		BehaviorHudText * behaviorHudtext = (BehaviorHudText*)behavior;
		BehaviorRead(behavior, stream);
		strcpy_s(behaviorHudtext->formatString, _countof(behaviorHudtext->formatString), StreamReadToken(stream));
		behaviorHudtext->scoreSystemId = StreamReadInt(stream);
	}
}
	
static void BehaviorHudTextUpdateText(BehaviorHudText* behvaiorText)
{
	if (behvaiorText)
	{
		if (behvaiorText->scoreSystemId != SsiInvalid)
		{
			behvaiorText->displayValue = ScoreSystemGetValue(behvaiorText->scoreSystemId);
			sprintf_s(behvaiorText->displayString, _countof(behvaiorText->displayString), behvaiorText->formatString, behvaiorText->displayValue);
		}
	}
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

