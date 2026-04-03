//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SpriteSource.h"
#include "DGL.h"
#include "Stream.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------


typedef struct SpriteSource
{
	// The dimensions of the sprite sheet.
	// (Hint: These should be initialized to (1, 1).)
	int	numRows;
	int	numCols;

	char name[32];
	// Pointer to a texture resource created using the DigiPen Graphics Library (DGL).
	const DGL_Texture* texture;

} SpriteSource;

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

SpriteSource* SpriteSourceCreate()
{
	SpriteSource *spriteSource = calloc(1, sizeof(SpriteSource));
	if (spriteSource)
	{
		spriteSource->numCols = 1;
		spriteSource->numRows = 1;
		return spriteSource;
	}
	else
	{
		return NULL;
	}

}

void SpriteSourceFree(SpriteSource** spriteSource)
{
	DGL_Graphics_FreeTexture(&(*spriteSource)->texture);
	free(*spriteSource);
	*spriteSource = NULL;
}
void SpriteSourceLoadTexture(SpriteSource* spriteSource, int numCols, int numRows, const char* textureName)
{
	char buffer[256];
	sprintf_s(buffer, sizeof(buffer), "Assets/%s", textureName);
	spriteSource->texture = DGL_Graphics_LoadTexture(buffer);
	spriteSource->numRows = numRows;
	spriteSource->numCols = numCols;

}
unsigned SpriteSourceGetFrameCount(const SpriteSource* spriteSource)
{
	if (spriteSource)
	{
		return spriteSource->numCols * spriteSource->numRows;
	}
	else
	{
		return 0;
	}
} 
void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, float* u, float* v)
{

	float col = 1.0f / spriteSource->numCols;
	float row = 1.0f / spriteSource->numRows;

	*u = col * (frameIndex % spriteSource->numCols);
	*v = row * (frameIndex / spriteSource->numCols);

}
	
void SpriteSourceSetTexture(const SpriteSource* spriteSource)
{  
	DGL_Graphics_SetTexture(spriteSource->texture);
}
void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned frameIndex)
{
	DGL_Vec2 uv = { 0,0 };
	SpriteSourceGetUV(spriteSource, frameIndex, &uv.x, &uv.y);
	DGL_Graphics_SetCB_TextureOffset(&uv);
}
void SpriteSourceRead(SpriteSource* spriteSource, Stream stream)
{
	if (spriteSource && stream)
	{
		const char *token = StreamReadToken(stream);
		if (!strncmp(token, "SpriteSource", _countof("SpriteSource")))
		{
		
			unsigned int columns, rows;
			token = StreamReadToken(stream);
 			strcpy_s(spriteSource->name, _countof(spriteSource->name), token);
			columns = StreamReadInt(stream);
			rows = StreamReadInt(stream);
			spriteSource->numCols = columns;
			spriteSource->numRows = rows;
			/*char buffer[256];*/
			const char *textureName = StreamReadToken(stream);
			/*sprintf_s(buffer, sizeof(buffer), "Assets/%s", textureName);*/
			spriteSource->texture = DGL_Graphics_LoadTexture(textureName);
		}
	}
}
bool SpriteSourceIsNamed(const SpriteSource* spriteSource, const char* name)
{
	if (spriteSource && name)
	{
		if (strcmp(name, spriteSource->name) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}