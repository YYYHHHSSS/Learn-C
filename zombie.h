#pragma once
#ifndef _ZOMBIE_H
#define _ZOMBIE_H

#include "Header.h"

#define Z_Height     110
#define Z_Width      75
#define Z_Sub        20
#define Z_Life       2.4
#define Z_Hurt       0.15
#define Z_Move       2
#define Z_Multi      1
#define Z_Pic        5

HBITMAP Lzombiebmp[Z_Pic + 1];
HBITMAP Rzombiebmp[Z_Pic + 1];

// ��ʬ��ʼ��
void Z_Create(AllType *z);

// ��������
void Z_Load(HWND hwnd);

// ��������
void Z_Paint(HDC hdc, HDC hdcmem, int i);


#endif // !_ZOMBIE_H