//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 1
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "level2Scene.h"
#include "level1Scene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "StubScene.h"
#include "stream.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Transform.h"
#include "DGL.h"
#include "Mesh.h"
#include "Entity.h"
#include "Physics.h"
#include "EntityFactory.h"
#include "Animation.h"
#include "Vector2D.h"
#include "CheatSystem.h"


//------------------------------------------------------------------------------
// Private Constants:
//
//------------------------------------------------------------------------------
 typedef enum Monkeystates
{
	MonkeyInvalid = -1,
	MonkeyIdle,
	MonkeyWalk,
	MonkeyJump

}Monkeystates;


	static const float groundHeight = -150.0f;
	static const float moveVelocity = 500.0f;
	static const float jumpVelocity = 1000.0f;
	static const Vector2D gravityNormal = { 0.0f, -1500.0f };
	static const Vector2D gravityNone = { 0.0f, 0.0f };

	static const Vector2D resetTranslation = { 0,-150.0f };
	static const Vector2D resetacelleration = { 0,0 };
	static const Vector2D resetvec = { 0,0 };
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;
	int numLives;


	// Add any scene-specific variables second.

} Level1Scene;
 static char livesBuffer[16];

 static Mesh* createdMesh = new Mesh();
 static SpriteSource* createdSpriteSource = new SpriteSource();
 static Entity* createdEntity = new Entity();
 static Sprite* createdSpirte = new Sprite();
 static const float wallDistance = 462.0f;
 static const float CheckSquareDistance = (75.0f * 75.0f);

 static Entity* monkeyEntity = new Entity();
 static Mesh* monkeyMesh = new Mesh();
 static Sprite* monkeySprite = new Sprite();
 static SpriteSource* monkeySpriteSourceIdle = new SpriteSource();
 static SpriteSource* monkeySpriteSourceWalk = new SpriteSource();
 static SpriteSource* monkeySpriteSourceJump = new SpriteSource();
 
 static Entity* livesTextEntity = new Entity();
 static Mesh* textMesh = new Mesh();
 static Sprite* textSprite = new Sprite();
 static SpriteSource* textSpriteSource = new SpriteSource;
 Monkeystates monkeyState = MonkeyInvalid;


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level1SceneMovementController(Entity* entity);
static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneUpdate(float dt);
static void Level1SceneExit(void);
static void Level1SceneUnload(void);
static void Level1SceneRender(void);
static void Level1SceneSetMonkeyState(Entity* entity, Monkeystates newState);
static void Level1SceneBounceController(Entity* entity);
static bool Level1SceneIsColliding(const Entity* entityA, const Entity* entityB);



//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload},0 
	
	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Level1 Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level1SceneGetInstance(void)
{
	return &(instance.base);
	
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level1SceneLoad(void)
{
	Stream streamFile = StreamOpen("Data/Level1_Lives.txt");
	if (streamFile)
	{
		instance.numLives = StreamReadInt(streamFile);
		StreamClose(&streamFile);
	}

	createdMesh->MeshBuildQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");
	createdSpriteSource->SpriteSourceLoadTexture( 1, 1, "PlanetTexture.png");
	monkeyMesh->MeshBuildQuad(0.5, 0.5, 1.0f / 3, 1.0f / 3, "Mesh3x3");
	monkeySpriteSourceIdle->SpriteSourceLoadTexture( 1, 1, "MonkeyIdle.png");
	monkeySpriteSourceWalk->SpriteSourceLoadTexture( 3, 3, "MonkeyWalk.png");
	monkeySpriteSourceJump->SpriteSourceLoadTexture(1, 1, "MonkeyJump.png");
	textMesh->MeshBuildQuad( 0.5f, 0.5f, 1.0f/16, 1.0f/8, "Mesh16x8");
	textSpriteSource->SpriteSourceLoadTexture(16, 8, "Roboto_Mono_black.png");


	
}




// Initialize the entities and variables used by the scene.
static void Level1SceneInit(void)
{
	livesTextEntity = EntityFactoryBuild("MonkeyLivesText");
	createdEntity = EntityFactoryBuild("PlanetBounce");
	monkeyEntity = EntityFactoryBuild("Monkey");
	
	if (createdEntity)
	{	
		createdEntity->Has(Sprite)->SpriteSetMesh(createdMesh);
		createdEntity->Has(Sprite)->SpriteSetSpriteSource(createdSpriteSource);
		createdEntity->Has(Sprite)->SpriteSetFrame(0);
	}
	if (monkeyEntity)
	{
		monkeyState = MonkeyInvalid;
		Level1SceneSetMonkeyState(monkeyEntity, MonkeyIdle);
	}
	if (livesTextEntity)
	{
	   textSprite = livesTextEntity->Has(Sprite);
	   textSprite->SpriteSetMesh(textMesh);
	   textSprite->SpriteSetSpriteSource(textSpriteSource);
	   sprintf_s(livesBuffer,sizeof(livesBuffer),"Lives: %d",instance.numLives);
	   textSprite->SpriteSetText(livesBuffer);
	}
	DGL_Color color = { 1, 1, 1, 1 };
	DGL_Graphics_SetBackgroundColor(&color);
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}


// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{

	Level1SceneMovementController(monkeyEntity);
	Level1SceneBounceController(createdEntity);
	createdEntity->EntityUpdate(dt);
	monkeyEntity->EntityUpdate(dt);
	livesTextEntity->EntityUpdate(dt);

	if (Level1SceneIsColliding(monkeyEntity, createdEntity))
	{
		instance.numLives--;

		if (instance.numLives <= 0)
		{
			SceneSystemSetNext(level2SceneGetInstance());
		}
		else
		{
		   
			SceneSystemRestart();
		
		}

	}
}

// Render any objects associated with the scene.
void Level1SceneRender(void)
{
	createdEntity->EntityRender();
	monkeyEntity->EntityRender();
	livesTextEntity->EntityRender();
}

// Free any objects associated with the scene.
static void Level1SceneExit(void)
{
	
	delete createdEntity;
	delete monkeyEntity;
	delete livesTextEntity;
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
	delete monkeySpriteSourceIdle;
	delete monkeySpriteSourceJump;
	delete monkeySpriteSourceWalk;
	delete createdSpriteSource;
	delete textSpriteSource;
	delete createdMesh;
	delete monkeyMesh;
	delete textMesh;


}

static void Level1SceneMovementController(Entity *entity)
{
	const Physics* physics = entity->Has(Physics);
	const Transform* transform = entity->Has(Transform);

	if (physics && transform)
	{
		Vector2D velocity = *physics->PhysicsGetVelocity();
		Vector2D translation = *transform->TransformGetTranslation();
	
		if (DGL_Input_KeyDown(VK_LEFT))
		{
			velocity.x = -moveVelocity;
			if (monkeyState != MonkeyJump)
			{
				Level1SceneSetMonkeyState(entity, MonkeyWalk); 
	
			}
		}
		else if (DGL_Input_KeyDown(VK_RIGHT))
		{
			velocity.x = moveVelocity;
			if (monkeyState != MonkeyJump)
			{
				Level1SceneSetMonkeyState(entity, MonkeyWalk);
			}
		}
		else
		{
			velocity.x = 0;
			if (monkeyState != MonkeyJump)
			{
				Level1SceneSetMonkeyState(entity, MonkeyIdle);
			}
		}
		if (DGL_Input_KeyTriggered(VK_UP))
		{
			Level1SceneSetMonkeyState(entity, MonkeyJump);
			velocity.y = jumpVelocity;
			entity->Has(Physics)->PhysicsSetAcceleration(&gravityNormal);	
		}
		if (translation.y < groundHeight)
		{
			translation.y = groundHeight;
			entity->Has(Transform)->TransformSetTranslation(&translation);
			velocity.y = 0;
			entity->Has(Physics)->PhysicsSetAcceleration(&gravityNone);
			Level1SceneSetMonkeyState(entity, MonkeyIdle);	

		
		}
		entity->Has(Physics)->PhysicsSetVelocity(&velocity);
	}

}

static void Level1SceneSetMonkeyState(Entity* entity, Monkeystates newState)
{
	Sprite* monkeySpriteLocal = entity->Has(Sprite);
	Animation* monkeyAnimationComponent = entity->Has(Animation);


	if (monkeyState != (Monkeystates)newState)
	{
		monkeyState = newState;
		switch (newState)
		{
		    case MonkeyIdle:
				monkeySpriteLocal->SpriteSetMesh(createdMesh);
				monkeySpriteLocal->SpriteSetSpriteSource(monkeySpriteSourceIdle);
				monkeyAnimationComponent->AnimationPlay(1, 0.0f, false);
			break;
	     	case MonkeyWalk:
				monkeySpriteLocal->SpriteSetMesh(monkeyMesh);
				monkeySpriteLocal->SpriteSetSpriteSource(monkeySpriteSourceWalk);
				monkeyAnimationComponent->AnimationPlay(8, 0.05f, true);
			break;
		    case MonkeyJump:
				monkeySpriteLocal->SpriteSetMesh(createdMesh);
				monkeySpriteLocal->SpriteSetSpriteSource(monkeySpriteSourceJump);
				monkeyAnimationComponent->AnimationPlay(1, 0.0f, false);
			break;
			default: break;
		}
		
	}
}






static void Level1SceneBounceController(Entity* entity)
{
	Physics* entityPhysics = entity->Has(Physics);
	Transform* entityTransform = entity->Has(Transform);


	if (entityPhysics && entityTransform)	
	{
		Vector2D position = *entityTransform->TransformGetTranslation();
		Vector2D velocity = *entityPhysics->PhysicsGetVelocity();
		if (position.x <= -wallDistance)
		{
			position.x = -wallDistance;
			velocity.x = -velocity.x;
		}
		else if (position.x >= wallDistance)
		{
			position.x = wallDistance;
			velocity.x = -velocity.x;
		}
		if (position.y <= groundHeight)
		{
			position.y = groundHeight + (groundHeight - position.y);
			velocity.y = -velocity.y;
		}

		entityPhysics->PhysicsSetVelocity(&velocity);
		entityTransform->TransformSetTranslation(&position);
	}

}
static bool Level1SceneIsColliding(const Entity* entityA, const Entity* entityB)
{
	
	Vector2D entityPositionA = *entityA->Has(Transform)->TransformGetTranslation();
	Vector2D entityPositionB = *entityB->Has(Transform)->TransformGetTranslation();

	if (Vector2DSquareDistance(&entityPositionA, &entityPositionB) <= CheckSquareDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
}




