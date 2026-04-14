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
#include "Entity.h"

typedef FILE* Stream;
class Entity;

class Behavior : public Component
{
public:
	Behavior() : Component(Component::cBehavior), timer(0), stateCurr(0), stateNext(0){};
	virtual ~Behavior() = 0 {};

	virtual Behavior* Clone() const = 0;

	void BehaviorRead(Stream stream);

	int getStateCurr() { return stateCurr; };

	int getStateNext() { return stateNext; };

	float getTimer() { return timer; };
	
	template<typename state>
	void setStateCurr(state _state)
	{
		stateCurr = static_cast<int>(_state);
	}


	void setTimer(float time)
	{
		timer = time;
	}
	

	template<typename state>  
	void setStateNext(state _state)
	{
		stateNext = static_cast<int>(_state);
	}


   void Update(float dt) override;

	void virtual onUpdate(float dt) = 0;

	void virtual onInit() = 0;

	void virtual onExit() = 0;



private:
	float	timer;
	int stateCurr;		
	int stateNext;

};
