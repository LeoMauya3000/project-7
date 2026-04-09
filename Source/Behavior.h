//------------------------------------------------------------------------------
//
// File Name:	Behavior.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Component.h"
//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------



class Entity;

typedef struct Behavior : public Component
{

	typedef void(*BehaviorFunctionPtr)(Behavior* behavior);
	typedef void(*BehaviorFunctionPtrDt)(Behavior* behavior, float dt);
public:
	Behavior() : Component(Component::cBehavior), memorySize(0), timer(0), stateCurr(0),stateNext(0), onInit(NULL),onUpdate(NULL),onExit(NULL) {};
	~Behavior() override {};

	Behavior* Clone() const override;

	void BehaviorRead(Stream stream);

	void Update(float dt) override;

private:
	unsigned int memorySize;
	int stateCurr;		
	int stateNext;
	BehaviorFunctionPtr		onInit;
	BehaviorFunctionPtrDt	onUpdate;
	BehaviorFunctionPtr		onExit;
	float	timer;

};
