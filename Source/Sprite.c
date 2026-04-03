//------------------------------------------------------------------------------
//
// File Name:	Sprite.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sprite.h"
#include "DGL.h"
#include "Stream.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "Transform.h"
#include "Trace.h"
#include "Matrix2D.h"
#include "MeshLibrary.h"
#include <math.h>
#include "SpriteSourceLibrary.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Sprite
{
	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The alpha transparency to use when drawing the sprite.
	float alpha;

	// The sprite source used when drawing (NULL = simple colored mesh).
	const SpriteSource* spriteSource;

	// The mesh used to draw the sprite.
	const Mesh* mesh;

	// Zero-terminated string used to display sprite text.
	const char* text;

} Sprite;


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

Sprite* SpriteCreate(void)
{
	Sprite* sprite = calloc(1, sizeof(Sprite));
	if (sprite)
	{
		sprite->alpha = 1.0f;
		return sprite;
	}
	else
	{
		return NULL;
	}
}

void SpriteFree(Sprite** sprite)
{
	if (*sprite)
	{
		free(*sprite);
		*sprite = NULL;
	}
	return;
}
void SpriteRead(Sprite* sprite, Stream stream)
{
	const SpriteSource* spriteLibrary = NULL;
	const Mesh* meshLibrary = NULL;
	sprite->frameIndex = StreamReadInt(stream);
	sprite->alpha = StreamReadFloat(stream);
	const char * token = StreamReadToken(stream);
	meshLibrary = MeshLibraryBuild(token);
	SpriteSetMesh(sprite,meshLibrary);
	const char* nameToken = StreamReadToken(stream);
	spriteLibrary = SpriteSourceLibraryBuild(nameToken);
	SpriteSetSpriteSource(sprite, spriteLibrary);
}
void SpriteRender(const Sprite* sprite, Transform* transform)
{
	 Matrix2D matrix = *TransformGetMatrix(transform);


	if (sprite->spriteSource != NULL)
	{
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);	
		SpriteSourceSetTexture(sprite->spriteSource);
		SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);	

	}
	else
	{
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	}

	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	DGL_Graphics_SetCB_Alpha(sprite->alpha);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	if (sprite->text == NULL)
	{

		matrix = *TransformGetMatrix(transform);
		DGL_Graphics_SetCB_TransformMatrix(&matrix);
		MeshRender(sprite->mesh);
	}
	else
	{
		int characterIndex = 0;
		const char* character = sprite->text;
		Matrix2D offset;
		Matrix2DIdentity(&offset);
		Matrix2DTranslate(&offset,TransformGetScale(transform)->x, 0);

		while (*character != '\0')
		{
			characterIndex = *character - ' ';
			SpriteSourceSetTextureOffset(sprite->spriteSource, characterIndex);
			DGL_Graphics_SetCB_TransformMatrix(&matrix);
			MeshRender(sprite->mesh);
			character++;
			Matrix2DConcat(&matrix, &offset, &matrix);
	
		}
	}
}
float SpriteGetAlpha(const Sprite* sprite)
{

	if (sprite)
	{
		return sprite->alpha;
	}
	else
	{
		return 0.0f;
	}
	
}
void SpriteSetAlpha(Sprite* sprite, float alpha)
{
	if (alpha > 1)
	{
		alpha = 1;
	}
	if (alpha < 0)
	{
		alpha = 0;
	}
	sprite->alpha = alpha;
}
void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex)
{
	//unsigned int maxFrameCount = SpriteSourceGetFrameCount(sprite->spriteSource);


	if (sprite)
	{
		if (frameIndex <= SpriteSourceGetFrameCount(sprite->spriteSource) && frameIndex >= 0)
		{


			sprite->frameIndex = frameIndex;
		}
	}
	TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
}
void SpriteSetMesh(Sprite* sprite, const Mesh* mesh)	
{
	if (sprite && mesh)
	{
	 sprite->mesh = mesh;

	}

}
void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource)
{
	if (sprite && spriteSource)
	{
		sprite->spriteSource = spriteSource;
	}
	
}
void SpriteSetText(Sprite* sprite, const char* text)
{
	if (sprite)
	{
		sprite->text = text;
     }
}

Sprite* SpriteClone(const Sprite* other)
{
	if (other)
	{
		Sprite *clonedSprite = calloc(1, sizeof(Sprite));
		if (clonedSprite)
		{
			clonedSprite->alpha = other->alpha;
			clonedSprite->frameIndex = other->frameIndex;
			clonedSprite->mesh = other->mesh;
			clonedSprite->spriteSource = other->spriteSource;
			clonedSprite->text = other->text;
			return clonedSprite;
		}
	}
	return NULL;
}

