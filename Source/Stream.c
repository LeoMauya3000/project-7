//------------------------------------------------------------------------------
//
// File Name:	StubScene.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Stream.h"
#include "Vector2D.h"
#include "Trace.h"




static FILE* streamFile;
static int integerRead;
static float floatRead;

Stream StreamOpen(const char* filePath)
{

	fopen_s(&streamFile, filePath, "rt");

	if (streamFile == NULL)
	{
		char errorMsg[256];
		strerror_s(errorMsg, sizeof(errorMsg), errno);
		TraceMessage("Error: StreamOpen could not open file %s; %s", filePath, errorMsg);
		return NULL;
	}
	else
	{
		return streamFile;
	}
}

int StreamReadInt(Stream stream)
{

	if (stream != NULL)
	{


		fscanf_s(stream, "%d", &integerRead);
		return integerRead;
	} 
	else
	{
		return 0;
	}
	
}


float StreamReadFloat(Stream stream)
{

	if (stream != NULL)
	{
		fscanf_s(stream, "%f", &floatRead);
		return floatRead;

	} 
	else
	{
		return 0;
	}
	
}
void StreamReadVector2D(Stream stream, Vector2D* vector)
{
	
	vector->x = StreamReadFloat(stream);
	vector->y = StreamReadFloat(stream);
} 

void StreamClose(Stream* stream)
{
	if(stream != NULL)
	{
		fclose(*stream);
		*stream = NULL;
	}	
}

const char* StreamReadToken(Stream stream)
{
	
	if (stream)
	{
		static char tokenBuffer[1024];
		tokenBuffer[0] = 0;
		fscanf_s(stream, "%s", tokenBuffer, (unsigned)_countof(tokenBuffer));
		return tokenBuffer;
	}
	else
	{
		return NULL;
	}
	
	
 
} 
bool StreamReadBoolean(Stream stream)
{
	if (stream)
	{
		static char tokenBuffer[1024];
		tokenBuffer[0] = 0;
		fscanf_s(stream, "%s", tokenBuffer, (unsigned)_countof(tokenBuffer));

		if(strncmp(tokenBuffer, "0", _countof("0")))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
void StreamReadColor(Stream stream, DGL_Color* color)
{
	if (stream && color)
	{
		color->r = StreamReadFloat(stream);
		color->g = StreamReadFloat(stream);
		color->b = StreamReadFloat(stream);
		color->a = StreamReadFloat(stream);
	}
	else if (color)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
		color->a = 0;
	}


}