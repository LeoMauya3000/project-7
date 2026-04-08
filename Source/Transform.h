//------------------------------------------------------------------------------
//
// File Name:	Transform.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Component.h"

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------
class Entity;
typedef struct DGL_Mat4 Matrix2D;
typedef struct DGL_Vec2 Vector2D;
struct _iobuf;
typedef struct _iobuf FILE;
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------
class  Transform : public Component
{
    public:

		Transform();
		~Transform()override{};
	      
		Transform& TransformClone(const Transform* other);

		void TransformRead(Stream stream);

		const Matrix2D* TransformGetMatrix();

		const Vector2D* TransformGetTranslation();

		float TransformGetRotation();

		const Vector2D* TransformGetScale();

		void TransformSetTranslation(const Vector2D* translation);

		void TransformSetRotation(float rotation);

		void TransformSetScale(const Vector2D* scale);


    private:
	Vector2D  translation;
	float	  rotation;
	Vector2D   scale;
	bool	   isDirty;
	Matrix2D   matrix;

};
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------



