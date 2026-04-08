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

Transform::Transform()
{
	Vector2DSet(&this->scale, 1.0f, 1.0f);
	Vector2DSet(&this->translation, 0.0f, 0.0f);
	Matrix2DIdentity(&this->matrix);
	this->rotation = 0;
	this->isDirty = true;
}
void Transform::TransformRead(Stream stream)
{
	if (stream)
	{
		StreamReadVector2D(stream, &(this->translation));
		this->rotation = StreamReadFloat(stream);
		StreamReadVector2D(stream, &(this->scale));
	}
}
const Vector2D* Transform::TransformGetTranslation()
{
	if (this)
	{
		return &(this->translation);
		
	}
	return NULL;
}

float Transform::TransformGetRotation()
{
	if (this)
	{
		return this->rotation;
	}
	return 0;
}

const Vector2D* Transform::TransformGetScale()
{
	// Verify that a valid transform was specified.
	if (this)
	{
		return &(this->scale);

	}
	return NULL;
}

// Set the translation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new translation.
void Transform::TransformSetTranslation(const Vector2D* translation)
{
	if (this)
	{
		this->translation = *translation;
		this->isDirty = true;
	}
	
}

// Set the rotation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 rotation = The rotation value (in radians).
void Transform::TransformSetRotation(float rotation)
{
	// Verify that a valid transform was specified.
	if (this)
	{
		this->rotation = rotation;
		this->isDirty = true;
	}
}

// Set the scale of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new scale.
void Transform::TransformSetScale(const Vector2D * scale)
{
	// Verify that a valid transform was specified.
	if (this)
	{
		this->scale = *scale;
		this->isDirty = true;
	}
}
const Matrix2D* Transform::TransformGetMatrix()
{
	Matrix2D result1;
	Matrix2D rotaionMatrix;
	Matrix2D scaleMatrix;
	Matrix2D translationMatrix;
	Matrix2DIdentity(&result1);
	Matrix2DIdentity(&rotaionMatrix);
	Matrix2DIdentity(&scaleMatrix);
	Matrix2DIdentity(&translationMatrix);
	if (this)
	{
		if (this->isDirty)
		{
			Matrix2DScale(&scaleMatrix,this->scale.x, this->scale.y);
			Matrix2DRotRad(&rotaionMatrix, this->rotation);
			Matrix2DTranslate(&translationMatrix, this->translation.x, this->translation.y);
			Matrix2DConcat(&result1, &rotaionMatrix,&scaleMatrix);
			Matrix2DConcat(&this->matrix, &translationMatrix, &result1);
		}
		return &this->matrix;
	}
	else
	{
		return NULL;
	}
}


Transform* Transform::Clone() const
{
	return new Transform(*this);
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

