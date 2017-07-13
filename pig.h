#pragma once
#ifndef _PIG_H
#define _PIG_H

#include "Header.h"

#define P_Height     80
#define P_Width      80
#define P_Sub        -20
#define P_Life       1.6
#define P_Hurt       0.22
#define P_Move       3
#define P_Multi      1
#define P_Pic        3

HBITMAP Lpigbmp[P_Pic + 1];
HBITMAP Rpigbmp[P_Pic + 1];

// Ұ���ʼ��
void P_Create(AllType *p);

// ��������
void P_Load(HWND hwnd);

// ��������
void P_Paint(HDC hdc, HDC hdcmem, int i);


#endif // !_PIG_H