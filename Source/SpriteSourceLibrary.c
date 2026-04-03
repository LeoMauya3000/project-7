//------------------------------------------------------------------------------
//
// File Name:	SpriteSourceLibrary.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SpriteSourceLibrary.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Stream.h"
#define MAX_SPRITE_ENTRY 10

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct SpriteSourceLibrary
{
	// The number of sprite sources currently in the list.
	unsigned int spriteSourceCount;

	// A list of all currently loaded sprite sources.
	// This list can be a fixed-length array (minimum size of 10 entries)
	// or a dynamically-sized array, such as a linked list.
	const SpriteSource* spriteSourceList[MAX_SPRITE_ENTRY];

} SpriteSourceLibrary;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static SpriteSourceLibrary sprites;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

static void SpriteSourceLibraryAdd(const SpriteSource* sprite);
static const SpriteSource* SpriteSourceLibraryFind(const char* SpriteName);



// Initialize the ...
void SpriteSourceLibraryInit()
{
	sprites.spriteSourceCount = 0;
	for (int i = 0; i < MAX_SPRITE_ENTRY; i++)
	{
		sprites.spriteSourceList[i] = 0;
	}

}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void SpriteSourceLibraryUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);
}

// Shutdown the ...
void SpriteSourceLibraryExit()
{

}

const SpriteSource* SpriteSourceLibraryBuild(const char* spriteSourceName)
{
	
		if (spriteSourceName)
		{
			if (SpriteSourceLibraryFind(spriteSourceName))
			{
				const SpriteSource* ReturnedSprite = SpriteSourceLibraryFind(spriteSourceName);
				return ReturnedSprite;
			}
			else
			{
				char buffer[256];
				sprintf_s(buffer, sizeof(buffer), "Data/%s.txt", spriteSourceName);
				Stream streamFile = StreamOpen(buffer);
				if (streamFile)
				{

					SpriteSource* spriteSource = SpriteSourceCreate();
					SpriteSourceRead(spriteSource, streamFile);
					SpriteSourceLibraryAdd(spriteSource);
					StreamClose(&streamFile);
					return spriteSource;
				}
			}

		}
		return NULL;
}
void SpriteSourceLibraryFreeAll()
{
	for (unsigned int i = 0; i < sprites.spriteSourceCount; i++)
	{
		if (sprites.spriteSourceList[i])
		{
			SpriteSourceFree(&sprites.spriteSourceList[i]);	
		}
	}
	sprites.spriteSourceCount = 0;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
static void SpriteSourceLibraryAdd(const SpriteSource* sprite)
{
		if (sprite)
		{
			if (sprites.spriteSourceCount < MAX_SPRITE_ENTRY)
			{
				sprites.spriteSourceList[sprites.spriteSourceCount] = sprite;
				sprites.spriteSourceCount++;
			}
			else
			{
				printf("sprite Library is full!");
			}

		}
}
static const SpriteSource* SpriteSourceLibraryFind(const char* SpriteName)
{
	if (SpriteName)
	{
		for (unsigned int i = 0; i < sprites.spriteSourceCount; i++)
		{
			if (SpriteSourceIsNamed(sprites.spriteSourceList[i], SpriteName))
			{
				return sprites.spriteSourceList[i];
			}
		}
	}
	return NULL;
}
