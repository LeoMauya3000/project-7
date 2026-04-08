//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 1
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "level2Scene.h"
#include "Stream.h"
#include "Mesh.h"
//#include "SandboxScene.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Sprite.h"
#include "DGL.h"
#include "Vector2D.h"
#include "Physics.h"
#include "Transform.h"
#include "level1Scene.h"
//#include "DemoScene.h"



//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const float spaceshipSpeed = 500.0f;
static const Vector2D resetVec = { 0,0 };

static float* spriteAlpha1;
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------







typedef struct level2Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;
	 Mesh* createdMesh = new Mesh();
	 Entity* createdEntity = new Entity();

	// Add any scene-specific variables second.

} level2Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void Level2SceneMovementController(Entity* entity);
static void level2SceneLoad(void);
static void level2SceneInit(void);
static void level2SceneUpdate(float dt);
static void level2SceneExit(void);
static void level2SceneUnload(void);
static void level2SceneRender(void);
static Stream streamFileLives;
static Stream streamFileHealth;

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static level2Scene instance =
{
	// Initialize the base structure:
	{ "Level2", level2SceneLoad, level2SceneInit, level2SceneUpdate, level2SceneRender, level2SceneExit, level2SceneUnload }

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* level2SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void level2SceneLoad(void)
{


	instance.createdMesh->MeshBuildSpaceship();


}

// Initialize the entities and variables used by the scene.
static void level2SceneInit()
{
	instance.createdEntity = EntityFactoryBuild("SpaceshipHoming");
	if (instance.createdEntity)
	{
		instance.createdEntity->Has(Sprite)->SpriteSetMesh(instance.createdMesh);
	}
	DGL_Color  color = { 0,0,0 };
	DGL_Graphics_SetBackgroundColor(&color);
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void level2SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	Level2SceneMovementController(instance.createdEntity);
	instance.createdEntity->EntityUpdate(dt);


	if (DGL_Input_KeyTriggered('Z'))
	{
		instance.createdEntity->Has(Sprite)->SpriteSetAlpha(0.5f);
	}
	if (DGL_Input_KeyTriggered('X'))
	{
		instance.createdEntity->Has(Sprite)->SpriteSetAlpha(1.0f);
	}


	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	
}

// Render any objects associated with the scene.
void level2SceneRender(void)
{
	instance.createdEntity->EntityRender();
}

// Free any objects associated with the scene.
static void level2SceneExit()
{
	delete instance.createdEntity;
}

// Unload any resources used by the scene.
static void level2SceneUnload(void)
{
	// pretty sure this a double free
}

static void Level2SceneMovementController(Entity* entity)
{
	Physics* physics = entity->Has(Physics);
	Transform * transform = entity->Has(Transform);


	if (physics && transform)
	{
		const Vector2D worldPos = DGL_Input_GetMousePosition();
		Vector2D mouse = DGL_Camera_ScreenCoordToWorld(&worldPos);
		Vector2D direction = { 0,0 };
		Vector2DSub(&direction, &mouse, transform->TransformGetTranslation());
		Vector2DNormalize(&direction, &direction);
		transform->TransformSetRotation(Vector2DToAngleRad(&direction));
		Vector2DScale(&direction, &direction, spaceshipSpeed);
		physics->PhysicsSetVelocity(&direction);
	}
}

