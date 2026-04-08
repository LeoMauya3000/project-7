//------------------------------------------------------------------------------
//
// File Name:	Teleporter.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Teleporter.h"
#include "Vector2D.h"
#include "DGL.h"
#include "Entity.h"
#include "Transform.h"
#include "Physics.h"
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


static Vector2D screenSize;

// Initialize the ...
 void TeleporterInit()
{
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
 void TeleporterUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);
}

// Shutdown the ...
 void TeleporterExit()
{
}


void TeleporterUpdateEntity(Entity* entity)
{
	if (entity)
	{
		screenSize = DGL_Window_GetSize();
		Vector2D windowHalfSize;
		Vector2DScale(&windowHalfSize, &screenSize, 0.5f);
		Physics* entityPhysics = entity->Has(Physics);
		Transform* entityTransform = entity->Has(Transform);

		if (entityPhysics && entityTransform)
		{
			Vector2D entityVelocity = *entityPhysics->PhysicsGetVelocity();
			Vector2D entityPos = *entityTransform->TransformGetTranslation();
			if (entityVelocity.x > 0 && (entityPos.x > windowHalfSize.x))
			{
				entityPos.x = -entityPos.x;
				entityTransform->TransformSetTranslation(&entityPos);
			}
			if (entityVelocity.x < 0 && (entityPos.x < -windowHalfSize.x))
			{
				entityPos.x = -entityPos.x;
				entityTransform->TransformSetTranslation(&entityPos);
			}
			if (entityVelocity.y > 0 && (entityPos.y > windowHalfSize.y))
			{
				entityPos.y = -entityPos.y;
				entityTransform->TransformSetTranslation(&entityPos);
			}
			if (entityVelocity.y < 0 && (entityPos.y < -windowHalfSize.y))
			{
				entityPos.y = -entityPos.y;
				entityTransform->TransformSetTranslation(&entityPos);
			}
		}

	}
	
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

