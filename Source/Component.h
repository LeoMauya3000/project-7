#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>


class Entity;

class Component
{

public:
	
	enum  TypeEnum
	{
		cTransform, cPhysics, cSprite, cAnimation, cBehavior, cCollider
	};
	Component(TypeEnum type) : mType(type), mParent(nullptr) {}
	Component::TypeEnum Type() const { return mType; }
	virtual ~Component() = 0;

	void Parent(Entity* parent) { mParent = parent;}
	Entity* Parent() const { return mParent; }

	virtual Component* Clone() const = 0;
	//return new TYPE(*this);


	virtual void Update(float dt) { UNREFERENCED_PARAMETER(dt); };

	virtual void Render() const {};



		
   private:

	TypeEnum mType;
	Entity* mParent;



};