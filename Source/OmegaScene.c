//------------------------------------------------------------------------------
//
// File Name:	OmegaScene.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "crtdbg.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "OmegaScene.h"
#include "DGL.h"
#include "EntityFactory.h"
#include "Sprite.h"
#include "Entity.h"
#include "Mesh.h"
#include "BehaviorSpaceship.h"
#include "BehaviorBullet.h"
#include "MeshLibrary.h"
#include "Random.h"
#include "ScoreSystem.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

	static const unsigned cAsteroidSpawnInitial = 8;
	static const unsigned cAsteroidSpawnMaximum = 20;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct OmegaScene
{
	// WARNING: The base class must always be included first.
	Scene	base;
	Entity* spaceShip;
	Entity* asteriodWave;
	Entity* asteroidsScore;
	Entity* asteroidsHighScore;
	Entity* arena;
	unsigned asteroidSpawnCount;

	// Add any scene-specific variables second.

} OmegaScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static float randomFloat;
static int randomInt;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void OmegaSceneLoad(void);
static void OmegaSceneInit(void);
static void OmegaSceneUpdate(float dt);
static void OmegaSceneExit(void);
static void OmegaSceneUnload(void);
static void OmegaSceneRender(void);
static void OmegaSceneSpawnAsteroidWave(void);
static void OmegaSceneSpawnAsteroid(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static OmegaScene instance =
{
	// Initialize the base structure:
	{ "Stub", OmegaSceneLoad, OmegaSceneInit, OmegaSceneUpdate, OmegaSceneRender, OmegaSceneExit, OmegaSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* OmegaSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void OmegaSceneLoad(void)
{	
	ScoreSystemClear();
}

// Initialize the entities and variables used by the scene.
static void OmegaSceneInit()
{   
	DGL_Graphics_SetBackgroundColor(&(DGL_Color){ 0,0,0,0 });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	
	OmegaSceneSpawnAsteroidWave();
	instance.arena = EntityFactoryBuild("Arena");
	instance.spaceShip = EntityFactoryBuild("SpaceshipOmega");
 	instance.asteroidsScore = EntityFactoryBuild("OmegaScore");
	instance.asteroidsHighScore = EntityFactoryBuild("OmegaHighScore");
	instance.asteriodWave = EntityFactoryBuild("OmegaWave");
	ScoreSystemReset();
	instance.asteroidSpawnCount = cAsteroidSpawnInitial;
	
	if (instance.arena)
	{
		SceneAddEntity(instance.arena);
	}
	if (instance.spaceShip)
	{
		SceneAddEntity(instance.spaceShip);
	}
	if (instance.asteroidsScore)
	{
		SceneAddEntity(instance.asteroidsScore);
	}
	if (instance.asteroidsHighScore)
	{
		SceneAddEntity(instance.asteroidsHighScore);
	}
	if (instance.asteriodWave)
	{
		SceneAddEntity(instance.asteriodWave);
	}
	
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void OmegaSceneUpdate(float dt)
{
	
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
	if (!SceneFindEntityByName("Asteroid"))
	{
		OmegaSceneSpawnAsteroidWave();
	}	
	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	
}

// Render any objects associated with the scene.
void OmegaSceneRender(void)
{
}

// Free any objects associated with the scene.
static void OmegaSceneExit()
{
}

// Unload any resources used by the scene.
static void OmegaSceneUnload(void)
{
}

static void OmegaSceneSpawnAsteroidWave(void)
{
	ScoreSystemIncreaseWave();
	
	for (unsigned int i = 0; i < instance.asteroidSpawnCount; i++)
	{
		OmegaSceneSpawnAsteroid();
	}
	if (instance.asteroidSpawnCount < cAsteroidSpawnMaximum)
	{
		instance.asteroidSpawnCount++;
	}
}
static void OmegaSceneSpawnAsteroid(void)
{
		Entity* asteriod = EntityFactoryBuild("Asteroid");
		if (asteriod)
		{
			SceneAddEntity(asteriod);
		}
}

