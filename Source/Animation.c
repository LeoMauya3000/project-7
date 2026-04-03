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

typedef struct Animation
{
	// Pointer to the parent Entity associated with the Animation component.
	Entity* parent;

	// The current frame being displayed.
	unsigned int frameIndex;

	// The maximum number of frames in the sequence.
	unsigned int frameCount;

	// The time remaining for the current frame.
	float frameDelay;

	// The amount of time to display each successive frame.
	float frameDuration;

	// True if the animation is running; false if the animation has stopped.
	bool isRunning;

	// True if the animation loops back to the beginning.
	bool isLooping;

	// True if the end of the animation sequence has been reached, false otherwise.
	// (Hint: This should be true for only one game loop.)
	bool isDone;

} Animation;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void AdvanceFrame(Animation* animation);
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Animation* AnimationCreate(void)
{
	Animation* animationComponent = (Animation*)calloc(1, sizeof(Animation));
	return animationComponent;
}

void AnimationFree(Animation** animation)
{
	if (animation)
	{
		free(*animation);
		*animation = NULL;
	}
}
void AnimationRead(Animation* animation, Stream stream)
{


	if (animation && stream)
	{ 

		animation->frameIndex = StreamReadInt(stream);
		animation->frameCount = StreamReadInt(stream);
		animation->frameDelay = StreamReadFloat(stream);
		animation->frameDuration = StreamReadFloat(stream);
		animation->isRunning = StreamReadBoolean(stream);
		animation->isLooping = StreamReadBoolean(stream);
	}

}
void AnimationSetParent(Animation* animation, Entity* parent)
{
	if (animation && parent)
	{
		animation->parent = parent;
	}
}
void AnimationPlay(Animation* animation, int frameCount, float frameDuration, bool isLooping)
{
	if (animation)
	{
		animation->frameCount = frameCount;
		animation->frameDuration = frameDuration;
		animation->isLooping = isLooping;
		animation->isRunning = true;
		animation->frameIndex = 0;
		animation->frameDelay = frameDuration;
		animation->isDone = false;
		Sprite* entitySprite = EntityGetSprite(animation->parent);
		SpriteSetFrame(entitySprite, animation->frameIndex);
	}
	else
	{
		return;
	}
}

void AnimationUpdate(Animation* animation, float dt)
{
	if (animation)
	{
		animation->isDone = false;

		if (animation->isRunning)
		{
			animation->frameDelay -= dt;
		

			if (animation->frameDelay <= 0)
			{
				AdvanceFrame(animation);
			}
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}
bool AnimationIsDone(const Animation* animation)
{
	if (animation)
	{
		return animation->isDone;
	}

		return false;
}






static void AdvanceFrame(Animation* animation)
{
	if (animation)
	{
	    Sprite* entitySprite = EntityGetSprite(animation->parent);
	
		animation->frameIndex++;
		if (animation->frameIndex >= animation->frameCount)
		{

			if (animation->isLooping)
			{
				animation->frameIndex = 0;
				animation->isDone = true;	

			}
			else
			{
				animation->frameIndex = animation->frameCount - 1;
				animation->isRunning = false;
				animation->isDone = true;
			
			}
		}
			if (animation->isRunning)
			{
				
				SpriteSetFrame(entitySprite, animation->frameIndex);
				animation->frameDelay += animation->frameDuration;
				return;
			}
			else
			{
				animation->frameDelay = 0;
				return;
			}
			
	}
	else
	{

		return;
	}
}
Animation* AnimationClone(const Animation* other)
{
	if (other)
	{
		Animation* clonedAnimation = calloc(1, sizeof(Animation));

		if (clonedAnimation)
		{
		 *clonedAnimation = *other;
		 clonedAnimation->parent = NULL;
	   	 EntityAddAnimation(clonedAnimation->parent, clonedAnimation);
		 return clonedAnimation;

		}
	}
	return NULL;
}