//------------------------------------------------------------------------------
//
// File Name:	Mesh.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Mesh.h"
#include "DGL.h"
#include "stream.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const DGL_Color DGL_Color_Zero = { 0.0f, 0.0f, 0.0f, 0.0f };
static const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_White = { 1.0f, 1.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Red = { 1.0f, 0.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_Green = { 0.0f, 1.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
static const DGL_Vec2 Vertex_Pos_Right = { 0.5f, 0.0f };
static const DGL_Vec2 Vertex_Pos_Tlc = { -0.5f, 0.5f };
static const DGL_Vec2 Vertex_Pos_Trc = { 0.5f, 0.5f };
static const DGL_Vec2 Vertex_UV_Zero = { 0.0f, 0.0f };
static const DGL_Vec2 Vertex_Pos_Blc = { -0.5f, -0.5f };
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



void Mesh::MeshBuildQuad(float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
    DGL_Graphics_StartMesh();

	DGL_Vec2 v0 = { -xHalfSize, -yHalfSize };
	DGL_Vec2 v1 = { xHalfSize, yHalfSize };
	DGL_Vec2 v2 = { xHalfSize, -yHalfSize };
	DGL_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
	DGL_Vec2 u1 = { 0.0f, vSize };
	DGL_Vec2 u2 = { uSize, 0.0f };
	DGL_Vec2 u3 = { uSize, vSize };

	DGL_Vec2 v3 = { -xHalfSize, yHalfSize };


	DGL_Vec2 u4 = { 0.0f, 0.0f };

    DGL_Graphics_AddTriangle(
		&v0, &color, &u1,
        &v1, &color, & u2,
        &v2, &color, &u3);

    DGL_Graphics_AddTriangle(
        &v0, &color, &u1,
        &v3, &color, &u4,
        &v1, &color, &u2);

   
    this->meshResource = DGL_Graphics_EndMesh();
	strcpy_s(this->name, _countof(this->name), name);
}
void Mesh::MeshBuildSpaceship()
{
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		&Vertex_Pos_Right, &DGL_Color_Yellow, &Vertex_UV_Zero,
		&Vertex_Pos_Blc, &DGL_Color_Red, &Vertex_UV_Zero,
		&Vertex_Pos_Tlc, &DGL_Color_Red, &Vertex_UV_Zero);


	this->drawMode = DGL_DM_TRIANGLELIST;
	this->meshResource = DGL_Graphics_EndMesh();

}
void Mesh::Render()const
{
	if (this->meshResource)
	{
	  DGL_Graphics_DrawMesh(this->meshResource, this->drawMode);
	}
}

void Mesh::MeshRead(Stream stream)
{
	
	Vector2D position;
	DGL_Color color;
	Vector2D uvOffset;
	const char* token = StreamReadToken(stream);
	   if (!strncmp(token, "Quad", _countof("Quad")))
	   {
		   const char* quadName;
		   unsigned int columns, rows;
		   Vector2D  halfSize;  
		   StreamReadVector2D(stream, &halfSize);
		   columns = StreamReadInt(stream);
		   rows = StreamReadInt(stream);
		   quadName = StreamReadToken(stream);
		   Mesh::MeshBuildQuad(halfSize.x, halfSize.y, 1.0f/columns, 1.0f/rows, quadName);
	   }
		if (!strncmp(token, "Mesh", _countof("Mesh")))
		{
			const char* name = StreamReadToken(stream);
			strcpy_s(this->name, _countof(this->name), name);
			int verticies = StreamReadInt(stream);
			DGL_Graphics_StartMesh();

			for (int i = 0; i < verticies; i++)
			{
				 StreamReadVector2D(stream, &position);
				 StreamReadColor(stream, &color);
				 StreamReadVector2D(stream, &uvOffset);
				 DGL_Graphics_AddVertex(&position, &color, &uvOffset);
			}
 			this->meshResource = DGL_Graphics_EndMesh();
			this->drawMode = DGL_DM_TRIANGLELIST;
		}
}
bool Mesh::MeshIsNamed(const char* name)
{
	if (name)
	{
		if (strcmp(this->name, name) == 0)
		{
			return true;
		}
		return false;
	}
	return false;
}
Mesh:: ~Mesh()
{
	DGL_Graphics_FreeMesh(&this->meshResource);
}







