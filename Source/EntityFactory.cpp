//------------------------------------------------------------------------------
//
// File Name:	Stub.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Stream.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "EntityContainer.h"	


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
static EntityContainer* archetypes;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Entity* EntityFactoryBuild(const char* filename)
{
	Stream streamFile;
	Entity* entity;
	const char* token = NULL;

	if (filename)
	{
		Entity* archetype = archetypes->EntityContainerFindByName(filename);

		    if(archetype == NULL)
			{
				char pathName[FILENAME_MAX] = "";
				sprintf_s(pathName, _countof(pathName), "Data/%s.txt", filename);
				streamFile = StreamOpen(pathName);
				if (streamFile)
				{
					token = StreamReadToken(streamFile);
					if (!strncmp(token, "Entity", _countof("Entity")))
					{
						entity->EntityRead(streamFile);
						archetypes->EntityContainerAddEntity(entity);
						archetype = entity;
						
					}
				}
				StreamClose(&streamFile);
			}

			if (archetype)
			{
				return &entity->EntityClone(archetype);
			}



	}
		return NULL;
	
}
void EntityFactoryFreeAll()
{
	if (archetypes)
	{
		archetypes->EntityContainerFreeAll();
	}
}
