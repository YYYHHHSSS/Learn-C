#pragma once
#include <windows.h>

typedef struct LineWall
{
	double x1;
	double y1;

	double x2;
	double y2;
}CLINE;

typedef struct GAMEMAP
{
	int level;
	CLINE line[5];
	TCHAR *szText;
}CMAP;
