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

typedef struct Mesh
{
	// The name of the Mesh.  This will be used later in the semester.
	char name[32];

	// Pointer to the DGL_Mesh resource.
	const DGL_Mesh* meshResource;

	// The draw mode to use when rendering the mesh (Usually "DGL_DM_TRIANGLELIST").
	DGL_DrawMode drawMode;
} Mesh;

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

Mesh* MeshCreate()
{
	Mesh* mesh = calloc(1, sizeof(Mesh));
	if (mesh)
	{
		return mesh;
	}
	else
	{
		return NULL;
	}
	
}

void MeshBuildQuad(Mesh* mesh, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
	&(DGL_Vec2) { -xHalfSize, -yHalfSize}, & (DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, & (DGL_Vec2) { 0.0f, vSize },
	& (DGL_Vec2) {
	xHalfSize, yHalfSize}, & (DGL_Color) {
	0.0f, 0.0f, 0.0f, 1.0f}, & (DGL_Vec2) {uSize, 0.0f}, & (DGL_Vec2) {xHalfSize, -yHalfSize}, & 
	(DGL_Color) {0.0f, 0.0f, 0.0f, 1.0f}, & (DGL_Vec2) {uSize, vSize});
	DGL_Graphics_AddTriangle(&(DGL_Vec2) { -xHalfSize, -yHalfSize}, & (DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, & (DGL_Vec2) { 0.0f, vSize },& (DGL_Vec2) {
	-xHalfSize, yHalfSize}, & (DGL_Color) {0.0f, 0.0f, 0.0f, 1.0f}, & (DGL_Vec2) {0.0f, 0.0f},& (DGL_Vec2) {xHalfSize, yHalfSize}, & (DGL_Color) {0.0f, 0.0f, 0.0f, 1.0f}, & (DGL_Vec2) {uSize, 0.0f});
    mesh->meshResource = DGL_Graphics_EndMesh();
	strcpy_s(mesh->name, _countof(mesh->name), name);

}
void MeshBuildSpaceship(Mesh* mesh)
{
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		&Vertex_Pos_Right, &DGL_Color_Yellow, &Vertex_UV_Zero,
		&Vertex_Pos_Blc, &DGL_Color_Red, &Vertex_UV_Zero,
		&Vertex_Pos_Tlc, &DGL_Color_Red, &Vertex_UV_Zero);


	mesh->drawMode = DGL_DM_TRIANGLELIST;
	mesh->meshResource = DGL_Graphics_EndMesh();

}
void MeshRender(const Mesh* mesh)
{
	if (mesh && mesh->meshResource)
	{
	  DGL_Graphics_DrawMesh(mesh->meshResource, mesh->drawMode);
	}
}
void MeshFree(Mesh** mesh)
{
	if (mesh && *mesh)
	{
		printf("mesh Freed!\n");
		DGL_Graphics_FreeMesh(&((*mesh)->meshResource));
		free(*mesh);
		*mesh = NULL;
	}
	return;
}
void MeshRead(Mesh* mesh, Stream stream)
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
		   MeshBuildQuad(mesh, halfSize.x, halfSize.y, 1.0f/columns, 1.0f/rows, quadName);
	   }
		if (!strncmp(token, "Mesh", _countof("Mesh")))
		{
			const char* name = StreamReadToken(stream);
			strcpy_s(mesh->name, _countof(mesh->name), name);
			int verticies = StreamReadInt(stream);
			DGL_Graphics_StartMesh();

			for (int i = 0; i < verticies; i++)
			{
				 StreamReadVector2D(stream, &position);
				 StreamReadColor(stream, &color);
				 StreamReadVector2D(stream, &uvOffset);
				 DGL_Graphics_AddVertex(&position, &color, &uvOffset);
			}
 			mesh->meshResource = DGL_Graphics_EndMesh();
			mesh->drawMode = DGL_DM_TRIANGLELIST;
		}
}
bool MeshIsNamed(const Mesh* mesh, const char* name)
{
	if (mesh && name)
	{
		if (strcmp(mesh->name, name) == 0)
		{
			return true;
		}
		return false;
	}
	return false;
}







