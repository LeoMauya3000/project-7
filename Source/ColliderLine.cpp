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
#include "Collider.h"
#include "Entity.h"
#include "Transform.h"
#include "DGL.h"
#include "Vector2D.h"
#include "ColliderLine.h"
#include "Stream.h"
#include "Physics.h"
#define cLineSegmentMax 8



//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
typedef struct ColliderLineSegment
{
	// A single line segment (P0 and P1).
	Vector2D	point[2];
} ColliderLineSegment;


typedef struct ColliderLine
{
	// Inherit the base collider structure.
	Collider	base;

	// The number of line segments in the list.
	unsigned int		lineCount;

	// The individual line segments.
	// (NOTE: Make sure to allocate enough memory for all line segments!)
	ColliderLineSegment	lineSegments[cLineSegmentMax];

} ColliderLine;

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

// Initialize the ...


Collider* ColliderLineCreate(void)
{
	ColliderLine* colliderLine = (ColliderLine*)calloc(1, sizeof(ColliderLine));
	if (colliderLine)
	{
		colliderLine->base.memorySize = sizeof(ColliderLine);
		colliderLine->base.type = ColliderTypeLine;
		return (Collider*)colliderLine;
	}
	else
	{
		return false;
	}
}
void ColliderLineRead(Collider* collider, Stream stream)
{
	if (collider && stream)
	{
		int numberOfLines = StreamReadInt(stream);
		Vector2D p0;
		Vector2D p1;
		for (int i = 0; i < numberOfLines; i++)
		{
			StreamReadVector2D(stream, &p0);
			StreamReadVector2D(stream, &p1);
			ColliderLineAddLineSegment(collider, &p0, &p1);
		}
	}
}
void ColliderLineAddLineSegment(Collider* collider, const Vector2D* p0, const Vector2D* p1)
{
	if (collider && p0 && p1)
	{
		ColliderLine* colliderLine = (ColliderLine*)collider;
		colliderLine->lineSegments[colliderLine->lineCount].point[0] = *p0;
		colliderLine->lineSegments[colliderLine->lineCount].point[1] = *p1;
		colliderLine->lineCount++;
	
	}
}
bool ColliderLineIsCollidingWithCircle(const Collider* collider, const Collider* other)
{
	//CHECK THIS FUNCTION LATER DOWN THE ROAD THIS MAY OR MAY NOT BE THE BANE OF ALL EVIL ^^
	if (collider && other)
	{
		Physics* physcisComponent = NULL;
		Transform* transformComponent = NULL;
		ColliderLine* colliderLine1 = NULL;
		if (EntityGetPhysics(other->parent) && EntityGetTransform(other->parent))
		{
			physcisComponent = EntityGetPhysics(other->parent);
			transformComponent = EntityGetTransform(other->parent);
		}
		if (EntityGetPhysics(collider->parent) && EntityGetTransform(collider->parent))
		{
			physcisComponent = EntityGetPhysics(collider->parent);
			transformComponent = EntityGetTransform(collider->parent);
		}
		if (other->type == ColliderTypeLine)
		{
			colliderLine1 = (ColliderLine*)other;
		}
		if (collider->type == ColliderTypeLine)
		{
			colliderLine1 = (ColliderLine*)collider;
		}
		Vector2D vectorE;
		Vector2D shipVector;
		Vector2D normalizedVec;

		if (physcisComponent && transformComponent && colliderLine1)
		{
			for (unsigned int i = 0; i < colliderLine1->lineCount; i++)
			{
				float timeInsec;
				
				Vector2D p0 = colliderLine1->lineSegments[i].point[0];
				Vector2D p1 = colliderLine1->lineSegments[i].point[1];

				Vector2D bS = *PhysicsGetOldTranslation(physcisComponent);
				Vector2D bE = *TransformGetTranslation(transformComponent);

				Vector2D bI;

				Vector2DSub(&shipVector, &bE, &bS);
				Vector2DSub(&vectorE,&p1,&p0);
				normalizedVec.x = vectorE.y;
				normalizedVec.y = -vectorE.x;
				Vector2DNormalize(&normalizedVec, &normalizedVec);
		

				if (Vector2DDotProduct(&normalizedVec, &shipVector) == 0)
				{
					continue;
				}

				timeInsec = ((Vector2DDotProduct(&normalizedVec, &p0) - Vector2DDotProduct(&normalizedVec, &bS)) / Vector2DDotProduct(&normalizedVec, &shipVector));
				Vector2DScaleAdd(&bI, &shipVector, timeInsec, &bS);

				if ((Vector2DDotProduct(&normalizedVec, &bS) <= Vector2DDotProduct(&normalizedVec, &p0)) && (Vector2DDotProduct(&normalizedVec, &bE) < Vector2DDotProduct(&normalizedVec, &p0)))
				{
					continue;
				}
				if ((Vector2DDotProduct(&normalizedVec, &bS) >= Vector2DDotProduct(&normalizedVec, &p0) && (Vector2DDotProduct(&normalizedVec, &bE) > Vector2DDotProduct(&normalizedVec, &p0))))
				{
				   continue;
				}
				//trivial checks end

				if (Vector2DDotProduct(&(Vector2D){p1.x - p0.x, p1.y - p0.y }, &(Vector2D){ bI.x - p0.x, bI.y - p0.y }) < 0)
				{
					
					continue;
				}
				if (Vector2DDotProduct(&(Vector2D) { p0.x - p1.x, p0.y - p1.y }, & (Vector2D) { bI.x - p1.x, bI.y - p1.y }) < 0)
				{
					//uhhh maybe??

					continue;
				}
				Vector2D d = { p1.x - p0.x, p1.y - p0.y };
				Vector2D v = { bI.x - p0.x, bI.y - p0.y };
				float t = Vector2DDotProduct(&v, &d) / Vector2DDotProduct(&d, &d);


				// wait im pretty sure this  is  an entirely useless check
				if (t >= 0 && t <= 1)
				{
					float reflectAngle;
					float speed;
					Vector2D penetrationVec;
					Vector2D scaledPenVec;
					Vector2D incidentVec;
					Vector2D reflectionVec;
					Vector2D bR;
					Vector2D oldVelocity = *PhysicsGetVelocity(physcisComponent);
					Vector2D velocity;
					
					Vector2DSub(&incidentVec, &bE, &bI);
					float dotProd = Vector2DDotProduct(&incidentVec, &normalizedVec);
					Vector2DScale(&penetrationVec, &normalizedVec, dotProd);
					Vector2DScale(&scaledPenVec, &penetrationVec, 2);
					Vector2DSub(&reflectionVec, &incidentVec,&scaledPenVec);
					Vector2DAdd(&bR, &bI,&reflectionVec);
					reflectAngle = Vector2DToAngleRad(&reflectionVec);
					speed = Vector2DLength(&oldVelocity);
					Vector2DNormalize(&reflectionVec,&reflectionVec);
					Vector2DScale(&velocity, &reflectionVec, speed);
					PhysicsSetVelocity(physcisComponent, &velocity);
					TransformSetRotation(transformComponent, reflectAngle);
					TransformSetTranslation(transformComponent, &bR);
					return true; 
				}
			
			}
		}
		return false;
	}
	else
	{
		return false;
	}
	
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

