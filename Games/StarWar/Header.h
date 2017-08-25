#pragma once
#ifndef _Header_H
#define _Header_H

#include <Windows.h>
#include "LinkList.h"

// ����
typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}Direction;

// �����ƶ�����
typedef enum {
	NORMAL,
	FAST,
	FALL
}Type;

// ��������
typedef enum {
	BOSS, 
	MONSTER, 
	MUSH, 
	PIG, 
	ZOMBIE,
	BOSS1
}Name;

// ����
typedef struct{
	int x, y;
	double HP;
	double hurt;
	int step;
	int sub;
	int width;
	int height;
	double multi;
	Direction d;
	Type type;
	Name name;
	BOOL behit;
}Boss, Monster, Mush, Pig, Zombie, AllType;

// ����ͼ��
#define BITMAP_FILE_BK1 "D:\\Study\\���\\Project\\Project\\FIGHT\\BK\\1.bmp"
#define BITMAP_FILE_BK2 "D:\\Study\\���\\Project\\Project\\FIGHT\\BK\\2.bmp"
#define BITMAP_FILE_BK3 "D:\\Study\\���\\Project\\Project\\FIGHT\\BK\\3.bmp"
#define BITMAP_FILE_BK4 "D:\\Study\\���\\Project\\Project\\FIGHT\\BK\\4.bmp"
#define BITMAP_FILE_BK5 "D:\\Study\\���\\Project\\Project\\FIGHT\\BK\\5.bmp"
#define BITMAP_FILE_BK6 "D:\\Study\\���\\Project\\Project\\FIGHT\\BK\\6.bmp"

// �ƶ��Ͻ�
#define Border 222

// ��ʱ��
#define GAME 1
#define MENU 2 

// ����ͼ��
HBITMAP hbmpBackground;

// ���ڴ�С
#define Height    720
#define Width     1280

// ������ɫ
#define COLOR_Mark         RGB(204, 204, 255)
#define BOSSCOLOR_Mark     RGB(105, 206, 236)
#define BOSS1COLOR_Mark    RGB(47, 176, 207)

// �������
PLIST Army;
PLIST Army_PicNum;

// ��ʼ������洢
void init();

// ���ٹ���洢
void destorylist();

// ���ع�������
int ArmyNum();


#endif // !_Header_H