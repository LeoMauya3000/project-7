//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "DGL.h"
//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class SpriteSource
{
    public:

	void SpriteSourceLoadTexture(int numCols, int numRows, const char* textureName);

	void SpriteSourceRead(Stream stream);

	bool SpriteSourceIsNamed(const char* name);

	unsigned SpriteSourceGetFrameCount();

	void SpriteSourceGetUV(unsigned int frameIndex, float* u, float* v);


	void SpriteSourceSetTexture();


	void SpriteSourceSetTextureOffset(unsigned frameIndex);

    private:
	char name[32];
	int	numRows;
	int	numCols;
	const DGL_Texture* texture;

};


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------



/*----------------------------------------------------------------------------*/
