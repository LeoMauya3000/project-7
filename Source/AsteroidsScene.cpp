//------------------------------------------------------------------------------
//
// File Name:	AsteriodScene.c
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
#include "AsteroidsScene.h"
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

typedef struct AsteriodScene
{
	// WARNING: The base class must always be included first.
	Scene	base;
	Entity* spaceShip;
	Entity* asteriodWave;
	Entity* asteroidsScore;
	Entity* asteroidsHighScore;
	unsigned asteroidSpawnCount;

	// Add any scene-specific variables second.

} AsteriodScene;

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

static void AsteriodSceneLoad(void);
static void AsteriodSceneInit(void);
static void AsteriodSceneUpdate(float dt);
static void AsteriodSceneExit(void);
static void AsteriodSceneUnload(void);
static void AsteriodSceneRender(void);
static void AsteroidsSceneSpawnAsteroidWave(void);
static void AsteroidsSceneSpawnAsteroid(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static AsteriodScene instance =
{
	// Initialize the base structure:
	{ "Stub", AsteriodSceneLoad, AsteriodSceneInit, AsteriodSceneUpdate, AsteriodSceneRender, AsteriodSceneExit, AsteriodSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* AsteriodSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void AsteriodSceneLoad(void)
{	
	ScoreSystemClear();
}

// Initialize the entities and variables used by the scene.
static void AsteriodSceneInit()
{   
	DGL_Color color = { 0,0,0,0 };
	DGL_Graphics_SetBackgroundColor(&color);
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	
	instance.spaceShip = EntityFactoryBuild("Spaceship");
 	instance.asteroidsScore = EntityFactoryBuild("AsteroidsScore");
	instance.asteroidsHighScore = EntityFactoryBuild("AsteroidsHighScore");
	instance.asteriodWave = EntityFactoryBuild("AsteroidsWave");
	ScoreSystemReset();
	instance.asteroidSpawnCount = cAsteroidSpawnInitial;
	AsteroidsSceneSpawnAsteroidWave();
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
static void AsteriodSceneUpdate(float dt)
{
	
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
	if (!SceneFindEntityByName("Asteroid"))
	{
		AsteroidsSceneSpawnAsteroidWave();
	}	
	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	
}

// Render any objects associated with the scene.
void AsteriodSceneRender(void)
{
}

// Free any objects associated with the scene.
static void AsteriodSceneExit()
{
}

// Unload any resources used by the scene.
static void AsteriodSceneUnload(void)
{
}

static void AsteroidsSceneSpawnAsteroidWave(void)
{
	ScoreSystemIncreaseWave();
	
	for (unsigned int i = 0; i < instance.asteroidSpawnCount; i++)
	{
		AsteroidsSceneSpawnAsteroid();
	}
	if (instance.asteroidSpawnCount < cAsteroidSpawnMaximum)
	{
		instance.asteroidSpawnCount++;
	}
}
static void AsteroidsSceneSpawnAsteroid(void)
{
		Entity* asteriod = EntityFactoryBuild("Asteroid");
		if (asteriod)
		{
			SceneAddEntity(asteriod);
		}
}

