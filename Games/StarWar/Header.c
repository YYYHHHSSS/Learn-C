#include "Header.h"

HBITMAP hbmpBackground = NULL;

// ��ʼ������洢
void init() {
	Army = ListCreate(0);
	Army_PicNum = ListCreate(0);
}

// ���ٹ���洢
void destorylist() {
	ListClearAndFree(Army);
	ListClearAndFree(Army_PicNum);
}

// ���ع�������
int ArmyNum() {
	return ListSize(Army);
}