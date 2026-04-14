//------------------------------------------------------------------------------
//
// File Name:	Entity.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
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


#include "Stream.h"
#include <iostream>
#include <vector>
#include "component.h"

#define Has(type) GetComponent<type>(Component::c##type)


//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in Entity.c.




class Entity
{

  private:
	 char name[32];
	 std::vector<Component*> components;
	 bool isDestroyed;
  public:
	 Entity();
	 Entity(char* _name, bool isDestroyed);
	 ~Entity();

	 Entity* EntityClone();

	 void EntityRead(Stream stream);

	 void EntityDestroy();

	 bool EntityIsDestroyed() const;

	 void EntityAddComponent(Component *component);

	 void EntitySetName(const char* _name);

	 const char* EntityGetName() const;

	 bool EntityIsNamed(const char* _name) const;

	 Component* Get(Component::TypeEnum type) const;

	 template<typename type>
	 type* GetComponent(Component::TypeEnum typeId) const
	 {
		 return static_cast<type*>(Get(typeId));
	 }

	 void EntityUpdate(float dt);

	 void EntityRender(void);
  };
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------		
// Public Functions:
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------


