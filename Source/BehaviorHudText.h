//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Behavior.h"
#include "ScoreSystem.h"
//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------
typedef FILE* Stream;
class BehaviorHudText : public Behavior
{
public:
	enum  state
	{
		cHudTextInvalid = -1,
		cHudTextIdle,			
	};


	BehaviorHudText(Stream _stream)
	{
		this->BehaviorHudTextRead(_stream);
	}

	 void onInit() override;
	 void onUpdate( float dt) override;
	 void onExit() override {};
	 void BehaviorHudTextUpdateText();
	 BehaviorHudText* Clone() const override;

private:

	void BehaviorHudTextRead(Stream stream);

	ScoreSystemId scoreSystemId;

	char formatString[32];

	char displayString[32];

	unsigned displayValue;

};


