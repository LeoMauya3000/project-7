//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------


class EntityContainer
{
public:

	EntityContainer();
	~EntityContainer();

	bool EntityContainerAddEntity( Entity* entity);
	void EntityContainerFreeEntity(Entity* entity);

	Entity* EntityContainerFindByName(const char* entityName);

	bool EntityContainerIsEmpty();

	void EntityContainerUpdateAll(float dt);

	void EntityContainerCheckCollisions();

	void EntityContainerRenderAll();


	void EntityContainerFreeAll();



private:

	unsigned entityCount;

	unsigned entityMax;

	std::vector<Entity*> entities;

};




