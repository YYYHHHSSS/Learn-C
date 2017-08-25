#pragma once
#ifndef _MUSH_H
#define _MUSH_H

#include "Header.h"

#define MR_Height     70
#define MR_Width      70
#define MR_Sub        -20
#define MR_Life       2.4
#define MR_Hurt       0.24
#define MR_Move       2
#define MR_Multi      1.5
#define MR_Pic        9

HBITMAP mushbmp[MR_Pic + 1];

// Ģ����ʼ��
void MR_Create(AllType *mr);

// ��������
void MR_Load(HWND hwnd);

// ��������
void MR_Paint(HDC hdc, HDC hdcmem, int i);


#endif // !_MUSH_H