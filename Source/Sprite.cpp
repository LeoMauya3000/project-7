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
#include "Entity.h"

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

Sprite::~Sprite()
{
	delete this->spriteSource;
	delete this->mesh;
}


void Sprite::SpriteRead(Stream stream)
{
	//removed sprite and mesh variables and passed
	this->frameIndex = StreamReadInt(stream);
	this->alpha = StreamReadFloat(stream);
	const char * token = StreamReadToken(stream);
	this->mesh = MeshLibraryBuild(token);
	const char* nameToken = StreamReadToken(stream);
	this->spriteSource = SpriteSourceLibraryBuild(nameToken);
}

void Sprite::Render() const
{
	Transform* transform = Parent()->Has(Transform);
	Matrix2D matrix = *Parent()->Has(Transform)->TransformGetMatrix();


	if (this->spriteSource != NULL)
	{
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		this->spriteSource->SpriteSourceSetTexture();
		this->spriteSource->SpriteSourceSetTextureOffset(this->frameIndex);

	}
	else
	{
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	}

	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	DGL_Graphics_SetCB_Alpha(this->alpha);
	DGL_Color color = { 0.0f, 0.0f, 0.0f, 0.0f };
	DGL_Graphics_SetCB_TintColor(&color);
	if (this->text == NULL)
	{

		matrix = *transform->TransformGetMatrix();
		DGL_Graphics_SetCB_TransformMatrix(&matrix);
		this->mesh->MeshRender();

	}
	else
	{
		int characterIndex = 0;
		const char* character = this->text;
		Matrix2D offset;
		Matrix2DIdentity(&offset);
		Matrix2DTranslate(&offset, transform->TransformGetScale()->x, 0);

		while (*character != '\0')
		{
			characterIndex = *character - ' ';
			this->spriteSource->SpriteSourceSetTextureOffset(characterIndex);
			DGL_Graphics_SetCB_TransformMatrix(&matrix);
			this->mesh->MeshRender();
			character++;
			Matrix2DConcat(&matrix, &offset, &matrix);
		}
	}
}
float Sprite::SpriteGetAlpha()
{

	if (this)
	{
		return this->alpha;
	}
	else
	{
		return 0.0f;
	}
	
}
void Sprite::SpriteSetAlpha( float _alpha)
{
	if (_alpha > 1)
	{
		_alpha = 1;
	}
	if (_alpha < 0)
	{
		_alpha = 0;
	}
	this->alpha = alpha;
}
void Sprite::SpriteSetFrame(unsigned int frameIndex_)
{
	if (this)
	{
		if (frameIndex_ <= this->spriteSource->SpriteSourceGetFrameCount() && frameIndex_ >= 0)
		{
			this->frameIndex = frameIndex_;
		}
	}
	TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
}
void Sprite::SpriteSetMesh(const Mesh* _mesh)	
{
	if (!this)
	{
		TraceMessage("SpriteSetMesh called on null this!");
		return;
	}
	if (!_mesh)
	{
		TraceMessage("SpriteSetMesh called with null mesh!");
		return;
	}

	this->mesh = _mesh;

}
void Sprite::SpriteSetSpriteSource(const SpriteSource* _spriteSource)
{
	if (_spriteSource)
	{
		this->spriteSource = _spriteSource;
	}
	
}
void Sprite::SpriteSetText( const char* _text)
{
	if (this)
	{
		this->text = _text;
    }
}



Sprite* Sprite::Clone() const
{
	return new Sprite(*this);
}



