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
#include "DGL.h"
#include "Matrix2D.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------
class Entity;
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
	      
		Transform* Clone() const override;

		void TransformRead(Stream stream);

		const Matrix2D* TransformGetMatrix();

		const Vector2D* TransformGetTranslation() const;

		float TransformGetRotation() const;

		const Vector2D* TransformGetScale() const;

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



