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

SpriteSource::~SpriteSource()
{
	DGL_Graphics_FreeTexture(&(this->texture));
}

void SpriteSource::SpriteSourceLoadTexture(int numCols, int numRows, const char* textureName)
{
	char buffer[256];
	sprintf_s(buffer, sizeof(buffer), "Assets/%s", textureName);
	this->texture = DGL_Graphics_LoadTexture(buffer);
	this->numRows = numRows;
	this->numCols = numCols;

}
unsigned SpriteSource::SpriteSourceGetFrameCount() const
{
	if (this)
	{
		return this->numCols * this->numRows;
	}
	else
	{
		return 0;
	}
} 
void SpriteSource::SpriteSourceGetUV(unsigned int frameIndex, float* u, float* v) const
{

	float col = 1.0f / this->numCols;
	float row = 1.0f / this->numRows;

	*u = col * (frameIndex % this->numCols);
	*v = row * (frameIndex / this->numCols);

}
	
void  SpriteSource::SpriteSourceSetTexture() const
{  
	DGL_Graphics_SetTexture(this->texture);
}
void SpriteSource::SpriteSourceSetTextureOffset( unsigned frameIndex) const
{
	DGL_Vec2 uv = { 0,0 };
	this->SpriteSourceGetUV(frameIndex, &uv.x, &uv.y);
	DGL_Graphics_SetCB_TextureOffset(&uv);
}
void SpriteSource::SpriteSourceRead(Stream stream)
{
	if (stream)
	{
		const char *token = StreamReadToken(stream);
		if (!strncmp(token, "SpriteSource", _countof("SpriteSource")))
		{
		
			unsigned int columns, rows;
			token = StreamReadToken(stream);
 			strcpy_s(this->name, _countof(this->name), token);
			columns = StreamReadInt(stream);
			rows = StreamReadInt(stream);
			this->numCols = columns;
			this->numRows = rows;
			/*char buffer[256];*/
			const char *textureName = StreamReadToken(stream);
			/*sprintf_s(buffer, sizeof(buffer), "Assets/%s", textureName);*/
			this->texture = DGL_Graphics_LoadTexture(textureName);
		}
	}
}
bool  SpriteSource::SpriteSourceIsNamed(const char* name)const
{
	if (name)
	{
		if (strcmp(name, this->name) == 0)
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