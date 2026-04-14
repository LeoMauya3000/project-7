//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 6
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "stdafx.h"
#include "Collider.h"

typedef FILE* Stream;
class ColliderCircle : public Collider
{
public:

	ColliderCircle(Stream _stream) : Collider(ColliderTypeCircle)
	{
		ColliderCircleRead(_stream);
	}
	~ColliderCircle() override{};

	ColliderCircle* Clone() const override;

	void ColliderCircleRead(Stream stream);

	float ColliderCircleGetRadius();

	void ColliderCircleSetRadius(float radius);

	bool ColliderCircleIsCollidingWithCircle(const Collider* collider, const Collider* other);


private:
	float radius;

};


