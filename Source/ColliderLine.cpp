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

void ColliderLine::ColliderLineRead(Stream stream)
{
	if (stream)
	{
		int numberOfLines = StreamReadInt(stream);
		Vector2D p0;
		Vector2D p1;
		for (int i = 0; i < numberOfLines; i++)
		{
			StreamReadVector2D(stream, &p0);
			StreamReadVector2D(stream, &p1);
			this->ColliderLineAddLineSegment(&p0, &p1);
			
		}
	}
}
void  ColliderLine::ColliderLineAddLineSegment(const Vector2D* p0, const Vector2D* p1)
{
	if (p0 && p1)
	{
		this->lineSegments[this->lineCount].point[0] = *p0;
		this->lineSegments[this->lineCount].point[1] = *p1;
		this->lineCount++;
	
	}
}
bool ColliderLine::ColliderLineIsCollidingWithCircle(const Collider* collider, const Collider* other)
{

	if (collider && other)
	{
		Physics* physcisComponent = NULL;
		Transform* transformComponent = NULL;
		ColliderLine* colliderLine1 = NULL;
		if (other->Parent()->Has(Physics) && other->Parent()->Has(Transform))
		{
			physcisComponent = other->Parent()->Has(Physics);
			transformComponent = other->Parent()->Has(Transform);
		}
		if (collider->Parent()->Has(Physics) && collider->Parent()->Has(Transform))
		{
			physcisComponent = collider->Parent()->Has(Physics);
			transformComponent = collider->Parent()->Has(Transform);
		}
		if (other->ReturnColliderType() == ColliderTypeLine)
		{
			colliderLine1 = (ColliderLine*)other;
		}
		if (collider->ReturnColliderType() == ColliderTypeLine)
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

				Vector2D bS = * physcisComponent->PhysicsGetOldTranslation();
				Vector2D bE = *transformComponent->TransformGetTranslation();

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

				Vector2D side1 = { p1.x - p0.x, p1.y - p0.y };
				Vector2D side2 = { bI.x - p0.x, bI.y - p0.y };

				if (Vector2DDotProduct(&side1, &side2) < 0)
				{
					
					continue;
				}
				side1 = { p0.x - p1.x, p0.y - p1.y };
				side2 = { bI.x - p1.x, bI.y - p1.y };

				if (Vector2DDotProduct(&side1, &side2) < 0)
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
					Vector2D oldVelocity = *physcisComponent->PhysicsGetVelocity();
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
					physcisComponent->PhysicsSetVelocity(&velocity);
			        transformComponent->TransformSetRotation(reflectAngle);
				     transformComponent->TransformSetTranslation(&bR);
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


ColliderLine* ColliderLine::Clone() const
{
	return new ColliderLine(*this);
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

