//------------------------------------------------------------------------------
//
// File Name:	Random.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Random.h"


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

static unsigned int rngSeed;

// Initialize the ...
void RandomInit()
{
	srand(rngSeed);

}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void RandomUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);
}

// Shutdown the ...
void RandomExit()
{
}

int RandomRange(int rangeMin, int rangeMax)
{
	// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/rand.


	int randomInt = (int)(((double)rand() / RAND_MAX) * (rangeMax - rangeMin + 1) + rangeMin);
	return randomInt;
}
float RandomRangeFloat(float rangeMin, float rangeMax)
{
	// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/rand.


	float randomFloat =(float)((double)rand() / RAND_MAX) * (rangeMax - rangeMin + 1) + rangeMin;
	return randomFloat;

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

