//------------------------------------------------------------------------------
//
// File Name:	Matrix.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "DGL.h"
#include "Matrix2D.h"
#define _USE_MATH_DEFINES
 #include <math.h>

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

void Matrix2DIdentity(Matrix2D* pResult)
{	
	for (int i = 0; i < _countof(pResult->m[0]); i++)
	{
		for (int j = 0; j < _countof(pResult->m[0]); j++)
		{
			pResult->m[i][j] = 0;
		}
	}
	for (int i = 0; i < _countof(pResult->m[0]); i++)
	{
		pResult->m[i][i] = 1;
	}	

}

void Matrix2DTranspose(Matrix2D* pResult, const Matrix2D* pMtx)
{	
	for (int i = 0; i < _countof(pResult->m[0]); i++)
	{
		for (int j = 0; j < _countof(pResult->m[0]); j++)
		{
			pResult->m[i][j] = pMtx->m[j][i];	
		}
	}
}
void Matrix2DConcat(Matrix2D* pResult, const Matrix2D* pMtx0, const Matrix2D* pMtx1)
{
	Matrix2D temp = { 0 };

	for (int i = 0; i < _countof(pResult->m[0]); i++)
	{
		for (int j = 0; j < _countof(pResult->m[0]); j++)
		{
			temp.m[i][j] = (pMtx0->m[i][0] * pMtx1->m[0][j])  + (pMtx0->m[i][1] * pMtx1->m[1][j]) + 
				(pMtx0->m[i][2] * pMtx1->m[2][j]) + (pMtx0->m[i][3] * pMtx1->m[3][j]);
		}
	}
	*pResult = temp;
}
void Matrix2DTranslate(Matrix2D* pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][3] = x;
	pResult->m[1][3] = y;

}
void Matrix2DScale(Matrix2D* pResult, float x, float y)
{
	if (pResult)
	{
		Matrix2DIdentity(pResult);
		pResult->m[0][0] = x;
		pResult->m[1][1] = y;
		

		
	}
}
void Matrix2DRotDeg(Matrix2D* pResult, float angle)
{

	double radians = (angle * M_PI) / 180.0f;
	if (pResult)
	{
		Matrix2DIdentity(pResult);
		pResult->m[0][0] = cosf((float)radians);
		pResult->m[0][1] = -sinf((float)radians);
		pResult->m[1][0] = sinf((float)radians);
		pResult->m[1][1] = cosf((float)radians);
	}

}
void Matrix2DRotRad(Matrix2D* pResult, float angle)
{
	if (pResult)
	{
		Matrix2DIdentity(pResult);
		pResult->m[0][0] = cosf(angle);
		pResult->m[0][1] = -sinf(angle);
		pResult->m[1][0] = sinf(angle);
		pResult->m[1][1] = cosf(angle);
		
	}
}
void Matrix2DMultVec(Vector2D* pResult, const Matrix2D* pMtx, const Vector2D* pVec)
{
	if (pResult && pMtx && pVec)
	{
		float x = pVec->x;
		float y = pVec->y;

		pResult->x =
			(pMtx->m[0][0] * x) +
			(pMtx->m[0][1] * y) + 
			(pMtx->m[0][3] * 1.0f);

		pResult->y =
			(pMtx->m[1][0] * x) +
			(pMtx->m[1][1] * y) +
			(pMtx->m[1][3] * 1.0f);
	}
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

