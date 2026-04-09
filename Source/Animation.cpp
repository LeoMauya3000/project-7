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
#include "Animation.h"
#include "Stream.h"
#include "Sprite.h"
#include "Entity.h"

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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Animation::~Animation()
{
	this->frameIndex = 0;
	this->frameCount = 0;
	this->frameDelay = 0;
	this->frameDuration = 0;
	this->isRunning = false;
	this->isLooping = false;
}
void Animation::AnimationRead(Stream stream)
{
	if (stream)
	{ 
		this->frameIndex = StreamReadInt(stream);
		this->frameCount = StreamReadInt(stream);
		this->frameDelay = StreamReadFloat(stream);
		this->frameDuration = StreamReadFloat(stream);
		this->isRunning = StreamReadBoolean(stream);
		this->isLooping = StreamReadBoolean(stream);
	}

}
void Animation::AnimationPlay( int _frameCount, float _frameDuration, bool _isLooping)
{

	
		this->frameCount = _frameCount;
		this->frameDuration = _frameDuration;
		this->isLooping = _isLooping;
		this->isRunning = true;
		this->frameIndex = 0;
		this->frameDelay = this->frameDuration;
		this->isDone = false;
		Sprite* entitySprite = Parent()->GetComponent<Sprite>(Component::cSprite);
		entitySprite->SpriteSetFrame(this->frameIndex);
}

void Animation::Update(float dt)
{
		this->isDone = false;

		if (this->isRunning)
		{
			this->frameDelay -= dt;
		

			if (this->frameDelay <= 0)
			{
				Animation::AdvanceFrame();
			}
		}
		else
		{
			return;
		}

}
bool Animation::AnimationIsDone()
{
	if (this)
	{
		return this->isDone;
	}
    return false;
}





 void Animation::AdvanceFrame()
{
	if (this)
	{
		Sprite* entitySprite = Parent()->Has(Sprite);
	
		this->frameIndex++;
		if (this->frameIndex >= this->frameCount)
		{

			if (this->isLooping)
			{
				this->frameIndex = 0;
				this->isDone = true;

			}
			else
			{
				this->frameIndex = this->frameCount - 1;
				this->isRunning = false;
				this->isDone = true;
			
			}
		}
			if (this->isRunning)
			{
				entitySprite->SpriteSetFrame(this->frameIndex);
				this->frameDelay += this->frameDuration;
				return;
			}
			else
			{
				this->frameDelay = 0;
				return;
			}
			
	}
	else
	{

		return;
	}
}

 Animation* Animation::Clone()const
 {
	 return new Animation(*this);
 }



