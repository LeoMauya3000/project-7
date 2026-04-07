//------------------------------------------------------------------------------
//
// File Name:	Animation.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in Animation.c.

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.

class Entity;

class  Animation : public Component
{
    private:
	Entity* mParent;
	unsigned int frameIndex;
	unsigned int frameCount;
	float frameDelay;
	float frameDuration;
	bool isRunning;
	bool isLooping;
	bool isDone;

    public:
		Animation() : Component(Component::cAnimation), mParent(NULL), frameIndex(0),frameCount(0),frameDelay(0),frameDuration(0),isRunning(false),isLooping(false),
		 isDone(false){}

		~Animation() override;
		Animation::Animation(const Animation& other) : Component(other)
		{
			*this = other;
		}

		void AnimationRead(Stream stream);

		void AnimationPlay(int _frameCount, float _frameDuration, bool _isLooping);
		 void Update(float dt) override;
		 void Render() const override {};
	   Animation* Clone() const override = 0;
		bool AnimationIsDone();
		void AdvanceFrame();
};


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------







/*----------------------------------------------------------------------------*/



