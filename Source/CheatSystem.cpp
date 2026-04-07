//------------------------------------------------------------------------------
//
// File Name:	CheatSystem.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "DGL.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "CheatSystem.h"
#include "level1Scene.h"
#include "level2Scene.h"
//#include "AsteroidsScene.h"
#include "OmegaScene.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct CheatSystem
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} CheatSystem;

typedef struct CheatSystemKeyBinding
{
	char key;
	const Scene* (*getInstance)(void);

} CheatSystemKeyBinding;


static const CheatSystemKeyBinding keyBindings[] =
{
	{'1',Level1SceneGetInstance}, { '2',level2SceneGetInstance }
};
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void CheatSystemLoad(void);
static void CheatSystemInit(void);
static void CheatSystemUpdate(float dt);
static void CheatSystemExit(void);
static void CheatSystemUnload(void);
static void CheatSystemRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static CheatSystem instance =
{
	// Initialize the base structure:
	{ "CheatSystem", CheatSystemLoad, CheatSystemInit, CheatSystemUpdate, CheatSystemRender, CheatSystemExit, CheatSystemUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
BaseSystem* CheatSystemGetInstance(void)
{
	return (BaseSystem*)&(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void CheatSystemLoad(void)
{
}

// Initialize the entities and variables used by the scene.
static void CheatSystemInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void CheatSystemUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	for (int i = 0; i < _countof(keyBindings); i++)
	{
		if (DGL_Input_KeyTriggered(keyBindings[i].key))
		{
			if (keyBindings[i].key)
			{
				SceneRestart();
			}
			SceneSystemSetNext(keyBindings[i].getInstance());
		}
	}
}

// Render any objects associated with the scene.
void CheatSystemRender(void)
{
}

// Free any objects associated with the scene.
static void CheatSystemExit()
{
}

// Unload any resources used by the scene.
static void CheatSystemUnload(void)
{
}

