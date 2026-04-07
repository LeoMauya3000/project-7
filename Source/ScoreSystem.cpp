//------------------------------------------------------------------------------
//
// File Name:	ScoreSystem.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Windows.h>

#include "BaseSystem.h"
#include "ScoreSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ScoreSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;
	unsigned score;
	unsigned highScore;
	unsigned waveCount;

	// Add any system-specific variables second.

} ScoreSystem;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//  System-specific State functions:
static bool ScoreSystemInit(void);
static void ScoreSystemUpdate(float dt);
static void ScoreSystemRender(void);
static void ScoreSystemExit(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static ScoreSystem ScoreSysteminstance =
{
	{ "ScoreSystem", ScoreSystemInit, ScoreSystemUpdate, ScoreSystemRender, ScoreSystemExit},
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* ScoreSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&ScoreSysteminstance;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the Stub System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool ScoreSystemInit(void)
{
	// Return false if the system was NOT initialized successfully.
	// Return true if the system was initialized successfully.
	return true;
}

// Update the Stub System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void ScoreSystemUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
}

// Render any objects associated with the Stub System.
static void ScoreSystemRender(void)
{
}

// Shutdown the Stub System.
//   (HINT: Free any allocated resources and/or close any opened files).
static void ScoreSystemExit(void)
{
}

void ScoreSystemClear(void)
{
	ScoreSysteminstance.score = 0;
	ScoreSysteminstance.highScore = 0;
	ScoreSysteminstance.waveCount = 0;

}
void ScoreSystemReset(void)
{
	if (ScoreSysteminstance.score > ScoreSysteminstance.highScore)
	{
		ScoreSysteminstance.highScore = ScoreSysteminstance.score;
	}

	ScoreSysteminstance.score = 0;
	ScoreSysteminstance.waveCount = 0;

}
unsigned ScoreSystemGetValue(ScoreSystemId valueId)
{
	switch (valueId)
	{
	 case SsiScore:
	 {
		 return ScoreSysteminstance.score;
		 break;
	 }
	 case SsiHighScore:
	 {
		 return ScoreSysteminstance.highScore;
		 break;
	 }
	 case SsiWaveCount:
	 {
		 return ScoreSysteminstance.waveCount;
		 break;
	 }
	 default:
	 {
		 printf("improper value");
		 return 0;
		 break;
	 }
    }
}
void ScoreSystemIncreaseScore(unsigned amount)
{
	ScoreSysteminstance.score += amount;
}
void ScoreSystemIncreaseWave(void)
{
	ScoreSysteminstance.waveCount++;
}

