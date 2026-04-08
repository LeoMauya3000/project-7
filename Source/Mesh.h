//------------------------------------------------------------------------------
//
// File Name:	Mesh.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
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

// An example of the structure to be defined in Mesh.c.

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class  Mesh : public Component
{
    public:
	Mesh() : meshResource(NULL), drawMode(DGL_DM_TRIANGLELIST)
	{
		name[0] = '\0';
	}



	void MeshBuildQuad(float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name);

	void MeshBuildSpaceship();

	void MeshRead(Stream stream);

	bool MeshIsNamed(const char* name);

	void Render() const override {};

	~Mesh();

    private:
	char name[32];

	DGL_Mesh* meshResource;

	DGL_DrawMode drawMode;
};


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------












