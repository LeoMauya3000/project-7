//------------------------------------------------------------------------------
//
// File Name:	SandBoxScene.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 1
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Vector2D.h"
#include "Stream.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "SandBoxScene.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SandBoxScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} SandBoxScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

Stream vectorFile = NULL;

static void SandBoxSceneLoad(void);
static void SandBoxSceneInit(void);
static void SandBoxSceneUpdate(float dt);
static void SandBoxSceneExit(void);
static void SandBoxSceneUnload(void);
static void SandBoxSceneRender(void);
static void SandboxSceneTraceFloat(const char* text, float f);
static void SandboxSceneTraceVector(const char* text, const Vector2D* v);





//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static SandBoxScene instance =
{
	// Initialize the base structure:
	{ "Sandbox", SandBoxSceneLoad, SandBoxSceneInit, SandBoxSceneUpdate, SandBoxSceneRender, SandBoxSceneExit, SandBoxSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* SandBoxSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------





// Load any resources used by the scene.
static void SandBoxSceneLoad(void)
{
}

// Initialize the entities and variables used by the scene.
static void SandBoxSceneInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SandBoxSceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
	Vector2D vec1;
	float scale;
	float angle;

	vectorFile = StreamOpen("Data/VectorTests.txt");
	if (vectorFile)
	{
		
		Vector2DZero(&vec1);
		SandboxSceneTraceVector("Vector2DZero", &vec1);
		Vector2DSet(&vec1,1.5f,1.0f);
		SandboxSceneTraceVector("Vector2DSet", &vec1);
		Vector2DNeg(&vec1,&vec1);
		SandboxSceneTraceVector("Vector2DNeg", &vec1);
		Vector2DAdd(&vec1, &vec1, &vec1);
		SandboxSceneTraceVector("Vector2DAdd", &vec1);
		Vector2DSub(&vec1, &vec1, &vec1);
		SandboxSceneTraceVector("Vector2DSub", &vec1);
		StreamReadVector2D(vectorFile, &vec1);
		SandboxSceneTraceVector("StreamReadVector2D", &vec1);
		Vector2DNormalize(&vec1, &vec1);
		SandboxSceneTraceVector("Vector2DNormalize", &vec1);
		scale = StreamReadFloat(vectorFile);
		SandboxSceneTraceFloat("StreamReadFloat", scale);
		Vector2DScale(&vec1, &vec1, scale);
		SandboxSceneTraceVector("Vector2DScale", &vec1);
		Vector2DScaleAdd(&vec1, &vec1,scale,&vec1);
		SandboxSceneTraceVector("Vector2DScaleAdd", &vec1);
		Vector2DScaleSub(&vec1, &vec1, scale, &vec1);
		SandboxSceneTraceVector("Vector2DScaleSub", &vec1);
		SandboxSceneTraceFloat("Vector2DLength", Vector2DLength(&vec1));
		SandboxSceneTraceFloat("Vector2DSquareLength", Vector2DSquareLength(&vec1));
		Vector2D vec2;
		StreamReadVector2D(vectorFile, &vec2);
		StreamReadVector2D(vectorFile, &vec1);
		SandboxSceneTraceVector("StreamReadVector2D", &vec2);
		SandboxSceneTraceVector("StreamReadVector2D", &vec1);
		SandboxSceneTraceFloat("Vector2DDistance", Vector2DDistance(&vec1, &vec2));
		SandboxSceneTraceFloat("Vector2DSquareDistance", Vector2DSquareDistance(&vec1, &vec2));
		SandboxSceneTraceFloat("Vector2DDotProduct", Vector2DDotProduct(&vec2, &vec1));
		angle = StreamReadFloat(vectorFile);
		SandboxSceneTraceFloat("StreamReadFloat", angle);
		Vector2DFromAngleDeg(&vec1, angle);
		SandboxSceneTraceVector("Vector2DFromAngleDeg", &vec1);
		angle = StreamReadFloat(vectorFile);
		Vector2DFromAngleRad(&vec1, angle);
		SandboxSceneTraceFloat("StreamReadFloat", angle);
		SandboxSceneTraceVector("Vector2DFromAngleRad", &vec1);
		SandboxSceneTraceFloat("Vector2DToAngleRad", angle);
		

		
		




		
	}




	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	SceneSystemSetNext(NULL);
}

// Render any objects associated with the scene.
void SandBoxSceneRender(void)
{
}

// Free any objects associated with the scene.
static void SandBoxSceneExit()
{
}

// Unload any resources used by the scene.
static void SandBoxSceneUnload(void)
{
}

static void SandboxSceneTraceFloat(const char* text, float f)
{
	TraceMessage("Vector Test: %s = %f",text,f);
	
}
static void SandboxSceneTraceVector(const char* text, const Vector2D* v)
{
	TraceMessage("Vector Test: %s = [%f, %f]",text,v->x,v->y);
}



