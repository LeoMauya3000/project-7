//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MeshLibrary.h"
#include "EntityContainer.h"
#include "Entity.h"
#include "Mesh.h"
#include "Stream.h"

#define MESHLISTMAX 20
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct MeshLibrary
{
	// This variable is not required but could be used for tracking the number
	//   of Mesh objects currently in the list.
	unsigned int meshCount;

	// A list of all currently loaded meshes.
	// This list can be a fixed-length array (minimum size of 10 entries)
	// or a dynamically-sized array, such as a linked list.
	const Mesh* meshList[MESHLISTMAX];

} MeshLibrary;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static MeshLibrary meshes;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void MeshLibraryAdd(const Mesh* mesh);
static const Mesh* MeshLibraryFind(const char* meshName);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...
void MeshLibraryInit()
{
	meshes.meshCount = 0;
	for (unsigned int i = 0; i <  MESHLISTMAX; i++)
	{
		meshes.meshList[i] = 0;
	}
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void MeshLibraryUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);
}

// Shutdown the ...
void MeshLibraryExit()
{
}
const Mesh* MeshLibraryBuild(const char* meshName)
{

	if (meshName)
	{
		

		if (MeshLibraryFind(meshName))
		{

			const Mesh* ReturnedMesh = MeshLibraryFind(meshName);
			return ReturnedMesh;
		}
		else
		{
			char buffer[256];
			sprintf_s(buffer, sizeof(buffer), "Data/%s.txt", meshName);
			Stream streamFile = StreamOpen(buffer);
			if (streamFile)
			{
				
				Mesh* mesh = MeshCreate();
				MeshRead(mesh, streamFile);
				MeshLibraryAdd(mesh);
				StreamClose(&streamFile);
				return mesh;
			}
		}
	
    }
	return NULL;
	
}
void MeshLibraryFreeAll()
{
	for (unsigned int i = 0; i < meshes.meshCount; i++)
	{
		if (meshes.meshList[i])
		{
		  MeshFree(&meshes.meshList[i]);
		}
	}
	meshes.meshCount = 0;
}
static const Mesh* MeshLibraryFind(const char* meshName)
{
	if (meshName)
	{
		for (unsigned int i = 0; i < meshes.meshCount; i++)
		{
			if (MeshIsNamed(meshes.meshList[i], meshName))
			{
				return meshes.meshList[i];
			}
		}
	}
	return NULL;
}

static void MeshLibraryAdd(const Mesh* mesh)
{
	if (mesh)
	{
		if (meshes.meshCount <  MESHLISTMAX)
		{
			meshes.meshList[meshes.meshCount] = mesh;
			meshes.meshCount++;
		}
		else
		{
			printf("meshLibrary is full!");
		}
		
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

