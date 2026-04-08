//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "DGL.h"
//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in Sprite.c.


class Sprite : public Component
{

public:
	Sprite();
	~Sprite() override;

	Sprite* SpriteClone(const Sprite* other);

	void SpriteRead(Stream stream);

	void Render() const override {};

	float SpriteGetAlpha();

	void SpriteSetAlpha(float alpha);

	void SpriteSetFrame(unsigned int frameIndex);

	void SpriteSetMesh(const Mesh* mesh);

	void SpriteSetSpriteSource(SpriteSource* spriteSource);

	void SpriteSetText(const char* text);
	void Render() const override{};



private:

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
};
