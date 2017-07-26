#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H

#include "zombie.h"
#include "pig.h"
#include "boss1.h"
#include "monster.h"
#include "mush.h"
#include "boss.h"

typedef struct
{
	Direction d;
	int x, y;
	double HP;
	double hurt;
	double fire;
}Player;

#define BITMAP_FILE_LIFE        "D:\\Study\\���\\Project\\Project\\FIGHT\\INFO\\life.bmp"
#define BITMAP_FILE_BOSSLIFE    "D:\\Study\\���\\Project\\Project\\FIGHT\\INFO\\blife.bmp"
#define BITMAP_FILE_FIRE        "D:\\Study\\���\\Project\\Project\\FIGHT\\INFO\\fire.bmp"

#define Player_Height      90
#define Player_Width       60
#define P_Move             6
#define StartLife          12
#define InitHurt           0.8
#define InitFire           5
#define x_start            0
#define y_start            400
#define AttackDistance     37
#define BigDistance        30
#define Big_Width          120
#define Big_Height         90

#define Stand              13
#define Move               11
#define Attack             7
#define Big                5

HBITMAP Lstandbmp[Stand + 1];
HBITMAP Rstandbmp[Stand + 1];
HBITMAP Lmovebmp[Move + 1];
HBITMAP Rmovebmp[Move + 1];
HBITMAP Lattackbmp[Attack + 1];
HBITMAP Rattackbmp[Attack + 1];
HBITMAP Lbigbmp[Big + 1];
HBITMAP Rbigbmp[Big + 1];
HBITMAP hbmpLife;
HBITMAP hbmpBosslife;
HBITMAP hbmpFire;

// ���
Player player;
int stand;
int move;
int attack;
int big;
int bigx, bigy;
Direction bigd;
BOOL attackresponse;
BOOL bigstart;

// ��ʼ�����
void Player_Inite();

// վ��(��) ���롢����
void StandL_Load(HWND hwnd);
void StandL_Paint(HDC hdc, HDC hdcmem);

// վ��(��) ���롢����
void StandR_Load(HWND hwnd);
void StandR_Paint(HDC hdc, HDC hdcmem);

// �ƶ�(��) ���롢����
void MoveL_Load(HWND hwnd);
void MoveL_Paint(HDC hdc, HDC hdcmem);

// �ƶ�(��) ���롢����
void MoveR_Load(HWND hwnd);
void MoveR_Paint(HDC hdc, HDC hdcmem);

// ����(��) ���롢����
void AttackL_Load(HWND hwnd);

// ����(��) ���롢����
void AttackR_Load(HWND hwnd);

// ����(��) ���롢����
void BigL_Load(HWND hwnd);
void BigL_Paint(HDC hdc, HDC hdcmem);

// ����(��) ���롢����
void BigR_Load(HWND hwnd);
void BigR_Paint(HDC hdc, HDC hdcmem);

// ����ͼƬ
void LoadPlayer(HWND hwnd);
void LoadArmy(HWND hwnd);

// ������Ϣ
void LoadInfo(HWND hwnd);

// ��ʾ��Һ�BOSS����Ϣ
void PaintInfo(HDC hdc, HDC hdcmem);

// ���Ƶ���
void PaintArmy(HDC hdc, HDC hdcmem);

// ������ͼ
void AttackPaint(HWND hwnd);

// ����ƶ�
void PlayerMove(Direction d);

// ����Ƿ�����
BOOL IfDead();

#endif // !_PLAYER_H