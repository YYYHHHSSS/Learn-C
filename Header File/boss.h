#pragma once
#ifndef _BOSS_H
#define _BOSS_H

#include "Header.h"

#define B_Height     150
#define B_Width      120
#define B_Sub        60
#define B_Life       12
#define B_Hurt       0.4
#define B_Move       5
#define B_Multi      1
#define B_Pic        8

HBITMAP Lbossbmp[B_Pic + 1];
HBITMAP Rbossbmp[B_Pic + 1];

// ��׼���ʼ��
void B_Create(AllType *b);

// ��������
void B_Load(HWND hwnd);

// ��������
void BOSS_Paint(HDC hdc, HDC hdcmem, int i);


#endif // !_BOSS_H