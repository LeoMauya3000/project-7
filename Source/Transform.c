//------------------------------------------------------------------------------
//
// File Name:	Transform.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 2
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "DGL.h"
#include "Stream.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Matrix2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct Transform
{
	// The translation (or world position) of an entity.
	Vector2D	translation;

	// The rotation (or orientation) of an entity (in radians).
	float	rotation;

	// The scale (or size) of an entity.
	// (Hint: This should be initialized to (1, 1).)
	Vector2D	scale;

	// True if the transformation matrix needs to be recalculated.
	// (Hint: This should be initialized to true.)
	// (Hint: This should be set to true when the Transform data changes.)
	bool	isDirty;

	// The transformation matrix resulting from concatenating the matrices
	//   representing the translation, rotation, and scale transformations.
	//	 (e.g. matrix = Translation*Rotation*Scale matrices)
	Matrix2D	matrix;

} Transform;

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

// Dynamically allocate a new Transform component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: You must initialize the scale values to non-zero values.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Transform* TransformCreate(void)
{
	// Allocate the memory for the Transform component.
	Transform* transform = calloc(1, sizeof(Transform));

	// Initialize any non-zero member variables.
	if (transform)
	{
		Vector2DSet(&transform->scale, 1.0f, 1.0f);
		transform->isDirty = true;
	}

	// Return the allocated memory (NULL if unsuccessful).
	return transform;
}

// Free the memory associated with a Transform component.
// (NOTE: The Transform pointer must be set to NULL.)
// Params:
//	 transform = Pointer to the Transform pointer.
void TransformFree(Transform** transform)
{
	// Verify that a valid transform was specified.
	if (*transform)
	{
		// Free the allocated memory.
              		free(*transform);

		// Set the Transform pointer to NULL.
		*transform = NULL;
	}
}

// Read the properties of a Transform component from a file.
// [NOTE: Read the translation value using StreamReadVector2D.]
// [NOTE: Read the rotation value using StreamReadFloat.]
// [NOTE: Read the scale value using StreamReadVector2D.]
// Params:
//	 transform = Pointer to the Transform component.
//	 stream = Pointer to the data stream used for reading.
void TransformRead(Transform* transform, Stream stream)
{
	if (transform && stream)
	{
		StreamReadVector2D(stream, &(transform->translation));
		transform->rotation = StreamReadFloat(stream);
		StreamReadVector2D(stream, &(transform->scale));
	}
}

// Get the translation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's translation structure,
//		else return a NULL pointer.
const Vector2D* TransformGetTranslation(const Transform* transform)
{
	// Verify that a valid transform was specified.
	if (transform)
	{
		return &(transform->translation);
		
	}
	return NULL;
}

// Get the rotation value of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return the component's rotation value (in radians),
//		else return 0.0f.
float TransformGetRotation(const Transform* transform)
{
	// Verify that a valid transform was specified.
	if (transform)
	{
		  
		return transform->rotation;
	}
	return 0;
}

// Get the scale of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's scale,
//		else return a NULL pointer.
const Vector2D* TransformGetScale(const Transform* transform)
{
	// Verify that a valid transform was specified.
	if (transform)
	{
		return &(transform->scale);

	}
	return NULL;
}

// Set the translation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new translation.
void TransformSetTranslation(Transform* transform, const Vector2D* translation)
{
	// Verify that a valid transform was specified.
	
	
	
	if (transform)
	{
		transform->translation = *translation;
		transform->isDirty = true;
	}
	
}

// Set the rotation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 rotation = The rotation value (in radians).
void TransformSetRotation(Transform* transform, float rotation)
{
	// Verify that a valid transform was specified.
	if (transform)
	{
		transform->rotation = rotation;
		transform->isDirty = true;
	}
}

// Set the scale of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new scale.
void TransformSetScale(Transform* transform, const Vector2D * scale)
{
	// Verify that a valid transform was specified.
	if (transform)
	{
		transform->scale = *scale;
		transform->isDirty = true;
	}
}
const Matrix2D* TransformGetMatrix(Transform* transform)
{
	Matrix2D result1;
	Matrix2D rotaionMatrix;
	Matrix2D scaleMatrix;
	Matrix2D translationMatrix;
	Matrix2DIdentity(&result1);
	Matrix2DIdentity(&rotaionMatrix);
	Matrix2DIdentity(&scaleMatrix);
	Matrix2DIdentity(&translationMatrix);


	if (transform)
	{
		if (transform->isDirty)
		{
			Matrix2DScale(&scaleMatrix,transform->scale.x,transform->scale.y);
			Matrix2DRotRad(&rotaionMatrix, transform->rotation);
			Matrix2DTranslate(&translationMatrix, transform->translation.x, transform->translation.y);
			Matrix2DConcat(&result1, &rotaionMatrix,&scaleMatrix);
			Matrix2DConcat(&transform->matrix, &translationMatrix, &result1);
		
			/*
			
			printf("[%f %f % f %f]\n", transform->matrix.m[0][0], transform->matrix.m[0][1], transform->matrix.m[0][2], transform->matrix.m[0][3]);
			printf("[%f %f % f %f]\n", transform->matrix.m[1][0], transform->matrix.m[1][1], transform->matrix.m[1][2], transform->matrix.m[1][3]);
			printf("[%f %f % f %f]\n", transfor																																m->matrix.m[2][0], transform->matrix.m[2][1], transform->matrix.m[2][2], transform->matrix.m[2][3]);
			printf("[%f %f % f %f]\n", transform->matrix.m[3][0], transform->matrix.m[3][1], transform->matrix.m[3][2], transform->matrix.m[3][3]);
			transform->isDirty = false;
			*/

		}
		return &transform->matrix;
	}
	else
	{
		return NULL;
	}
}
Transform* TransformClone(const Transform* other)
{
	if (other)
	{
		Transform* clonedTransform = calloc(1, sizeof(Transform));
		if (clonedTransform)
		{
			clonedTransform->isDirty = other->isDirty;
			clonedTransform->matrix = other->matrix;
			clonedTransform->rotation = other->rotation;
			clonedTransform->scale = other->scale;
			clonedTransform->translation = other->translation;
			return clonedTransform;
		}
	}
	return NULL;
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

