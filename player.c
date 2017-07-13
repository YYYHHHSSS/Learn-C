#include "player.h"

BOOL attackresponse = FALSE;
BOOL bigstart = FALSE;

// ��ʼ�����
void Player_Inite() {

	player.x = x_start;
	player.y = y_start;
	player.d = RIGHT;

	player.HP = StartLife;
	player.hurt = InitHurt;
	player.fire = InitFire;
}

// վ��(��) ���롢����
void StandL_Load(HWND hwnd) {

	int i;
	TCHAR fileName[30] = { "" };

	for (i = 0; i <= Stand; i++) {
		wsprintf(fileName, ".\\FIGHT\\STAND\\L\\%d.bmp", i);
		Lstandbmp[i] = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 147, 215, LR_LOADFROMFILE);
	}

	stand = 0;
}
void StandL_Paint(HDC hdc, HDC hdcmem) {

	SetStretchBltMode(hdc, COLORONCOLOR);

	if (stand > Stand)
		stand = 0;

	SelectObject(hdcmem, Lstandbmp[stand]);
	TransparentBlt(hdc, player.x, player.y, Player_Width, Player_Height, hdcmem, 0, 0, 147, 215, COLOR_Mark);
	
	stand++;
}

// վ��(��) ���롢����
void StandR_Load(HWND hwnd) {

	int i;
	TCHAR fileName[30] = { "" };

	for (i = 0; i <= Stand; i++) {
		wsprintf(fileName, ".\\FIGHT\\STAND\\R\\%d.bmp", i);
		Rstandbmp[i] = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 147, 214, LR_LOADFROMFILE);
	}
}
void StandR_Paint(HDC hdc, HDC hdcmem) {

	SetStretchBltMode(hdc, COLORONCOLOR);

	if (stand > Stand)
		stand = 0;

	SelectObject(hdcmem, Rstandbmp[stand]);
	TransparentBlt(hdc, player.x, player.y, Player_Width, Player_Height, hdcmem, 0, 0, 147, 214, COLOR_Mark);
	
	move++;
}

// �ƶ�(��) ���롢����
void MoveL_Load(HWND hwnd) {

	int i;
	TCHAR fileName[30] = { "" };

	for (i = 0; i <= Move; i++) {
		wsprintf(fileName, ".\\FIGHT\\MOVE\\L\\%d.bmp", i);
		Lmovebmp[i] = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 152, 224, LR_LOADFROMFILE);
	}

	move = 0;
}
void MoveL_Paint(HDC hdc, HDC hdcmem) {

	SetStretchBltMode(hdc, COLORONCOLOR);

	if (move > Move)
		move = 0;

	SelectObject(hdcmem, Lmovebmp[move]);
	TransparentBlt(hdc, player.x, player.y, Player_Width, Player_Height, hdcmem, 0, 0, 152, 224, COLOR_Mark);
	
	move++;
}

// �ƶ�(��) ���롢����
void MoveR_Load(HWND hwnd) {

	int i;
	TCHAR fileName[30] = { "" };

	for (i = 0; i <= Move; i++) {
		wsprintf(fileName, ".\\FIGHT\\MOVE\\R\\%d.bmp", i);
		Rmovebmp[i] = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 151, 224, LR_LOADFROMFILE);
	}
}
void MoveR_Paint(HDC hdc, HDC hdcmem) {

	SetStretchBltMode(hdc, COLORONCOLOR);

	if (move >= Move)
		move = 0;

	SelectObject(hdcmem, Rmovebmp[move]);
	TransparentBlt(hdc, player.x, player.y, Player_Width, Player_Height, hdcmem, 0, 0, 151, 224, COLOR_Mark);
	
	move++;
}

// ����(��) ���롢����
void AttackL_Load(HWND hwnd) {

	int i;
	TCHAR fileName[30] = { "" };
	for (i = 0; i <= Attack; i++) {
		wsprintf(fileName, ".\\FIGHT\\ATTACK\\L\\%d.bmp", i);
		Lattackbmp[i] = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 275, 188, LR_LOADFROMFILE);
	}
	
	attack = 0;
}

// ����(��) ���롢����
void AttackR_Load(HWND hwnd) {

	int i;
	TCHAR fileName[30] = { "" };
	for (i = 0; i <= Attack; i++){
		wsprintf(fileName, ".\\FIGHT\\ATTACK\\R\\%d.bmp", i);
		Rattackbmp[i] = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 275, 187, LR_LOADFROMFILE);
	}
}

// ����(��) ���롢����
void BigL_Load(HWND hwnd) {

	int i;
	TCHAR fileName[30] = { "" };

	for (i = 0; i <= Big; i++) {
		wsprintf(fileName, ".\\FIGHT\\BIG\\L\\%d.bmp", i);
		Lbigbmp[i] = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 127, 93, LR_LOADFROMFILE);
	}
	
	big = 0;
}
void BigL_Paint(HDC hdc, HDC hdcmem) {

	SetStretchBltMode(hdc, COLORONCOLOR);

	if (big > Big)
		big = 0;

	SelectObject(hdcmem, Lbigbmp[big]);
	TransparentBlt(hdc, bigx, bigy, Big_Width, Big_Height, hdcmem, 0, 0, 127, 93, RGB(255, 255, 255));
	
	big++;
}

// ����(��) ���롢����
void BigR_Load(HWND hwnd) {

	int i;
	TCHAR fileName[30] = { "" };
	for (i = 0; i <= Big; i++){
		wsprintf(fileName, ".\\FIGHT\\BIG\\R\\%d.bmp", i);
		Rbigbmp[i] = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 127, 93, LR_LOADFROMFILE);
	}
}
void BigR_Paint(HDC hdc, HDC hdcmem) {

	SetStretchBltMode(hdc, COLORONCOLOR);

	if (big > Big)
		big = 0;

	SelectObject(hdcmem, Rbigbmp[big]);
	TransparentBlt(hdc, bigx, bigy, Big_Width, Big_Height, hdcmem, 0, 0, 127, 93, RGB(255, 255, 255));
	
	big++;
}

// ����ͼƬ
void LoadPlayer(HWND hwnd) {

	StandL_Load(hwnd);
	StandR_Load(hwnd);

	MoveL_Load(hwnd);
	MoveR_Load(hwnd);

	AttackL_Load(hwnd);
	AttackR_Load(hwnd);

	BigL_Load(hwnd);
	BigR_Load(hwnd);
}
void LoadArmy(HWND hwnd) {
	
	Z_Load(hwnd);
	P_Load(hwnd);
	B1_Load(hwnd);

	M_Load(hwnd);
	MR_Load(hwnd);
	B_Load(hwnd);	
}

// ������Ϣ
void LoadInfo(HWND hwnd) {

	hbmpLife = LoadImage(NULL, BITMAP_FILE_LIFE, IMAGE_BITMAP, 134, 117, LR_LOADFROMFILE);
	hbmpBosslife = LoadImage(NULL, BITMAP_FILE_BOSSLIFE, IMAGE_BITMAP, 134, 117, LR_LOADFROMFILE);
	hbmpFire = LoadImage(NULL, BITMAP_FILE_FIRE, IMAGE_BITMAP, 344, 471, LR_LOADFROMFILE);
}

// ��ʾ��Һ�BOSS����Ϣ
void PaintInfo(HDC hdc, HDC hdcmem) {

	int i, j, k;
	AllType *a;

	SetStretchBltMode(hdc, COLORONCOLOR);

	SelectObject(hdcmem, hbmpLife);

	for (i = 0; i < (int)player.HP; i++) {
		j = i > 5 ? i - 6 : i;
		TransparentBlt(hdc, 4 + j * 30, i > 5 ? 33 : 4, 24, 24, hdcmem, 0, 0, 134, 117, COLOR_Mark);
	}

	for (k = 0; k < (int)player.fire; k++) {
		SelectObject(hdcmem, hbmpFire);
		TransparentBlt(hdc, 4 + k * 30, i >= 7 ? 60 : 33, 24, 24, hdcmem, 0, 0, 344, 471, COLOR_Mark);
	}

	a = ListGetAt(Army, 0);
	if (NULL != a && (BOSS == a->name || BOSS1 == a->name)) {
		SelectObject(hdcmem, hbmpBosslife);
		for (i = 0; i < (int)a->HP; i++) {
			j = i > 5 ? i - 6 : i;
			TransparentBlt(hdc, 1237 - j * 30, i > 5 ? 33 : 4, 24, 24, hdcmem, 0, 0, 134, 117, COLOR_Mark);
		}
	}
}

// ���Ƶ���
void PaintArmy(HDC hdc, HDC hdcmem) {

	int i;
	AllType *a;

	for (i = 0; i < ArmyNum(); i++) {
		a = ListGetAt(Army, i);
		switch (a->name) {
		case BOSS:
			BOSS_Paint(hdc, hdcmem, i);
			break;
		case BOSS1:
			BOSS1_Paint(hdc, hdcmem, i);
			break;
		case MONSTER:
			M_Paint(hdc, hdcmem, i);
			break;
		case MUSH:
			MR_Paint(hdc, hdcmem, i);
			break;
		case PIG:
			P_Paint(hdc, hdcmem, i);
			break;
		case ZOMBIE:
			Z_Paint(hdc, hdcmem, i);
			break;
		}
	}

}

// ������ͼ
void AttackPaint(HWND hwnd) {

	HDC hdc, hdcmem;
	HDC test;
	HBITMAP hbmMem, hbmMem2;
	HFONT hFont, hOldFont;
	RECT rect;
	BITMAP bmp;

	GetClientRect(hwnd, &rect); //�ѿͻ����Ĵ�Сд��Rect�ṹ��
	hdc = GetDC(hwnd);

	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(hdcmem, hbmMem);

	test = CreateCompatibleDC(hdc);
	hbmMem2 = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(test, hbmMem2);

	// ========�������
	SelectObject(hdcmem, hbmpBackground);
	GetObject(hbmpBackground, sizeof(BITMAP), &bmp);
	StretchBlt(test, rect.left, rect.top, rect.right - rect.left,
		rect.bottom - rect.top, hdcmem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	// =====������
	SetStretchBltMode(hdc, COLORONCOLOR);
	SetStretchBltMode(hdcmem, COLORONCOLOR);

	if (attack >= Attack)
		attack = 0;
	if (player.d == RIGHT) {
		SelectObject(hdcmem, Rattackbmp[attack]);
		TransparentBlt(test, player.x, player.y + 1, 2 * Player_Width + 11, Player_Height, hdcmem, 0, 0, 275, 187, COLOR_Mark);
	}
	else {
		SelectObject(hdcmem, Lattackbmp[attack]);
		TransparentBlt(test, player.x - 71, player.y + 1, 2 * Player_Width + 11, Player_Height, hdcmem, 0, 0, 275, 188, COLOR_Mark);
	}
	attack++;

	// ========�������
	PaintArmy(test, hdcmem);

	// ���ƴ���
	if (TRUE == bigstart) {
		if (RIGHT == bigd) {
			BigR_Paint(test, hdcmem);
			bigx += 2 * P_Move;
		}
		else {
			BigL_Paint(test, hdcmem);
			bigx -= 2 * P_Move;
		}
	}
	if (bigx > Width || bigx < 0) {
		bigstart = FALSE;
		Clearbehit();
	}

	// =======�����Ϸ��Ϣ
	PaintInfo(test, hdcmem);

	// һ���Ի��Ƶ�Ŀ�괰��
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, test, 0, 0, SRCCOPY);

	DeleteObject(test);
	DeleteObject(hbmMem2);
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	ReleaseDC(hwnd, hdc);
}

// ����ƶ�
void PlayerMove(Direction d){

	switch (d) {
	case DOWN:
		if (player.y + P_Move + Player_Height < Height)
			player.y += P_Move;
		break;
	case UP:
		if (player.y - P_Move > Border)
			player.y -= P_Move;
		break;
	case LEFT:
		if (player.x - P_Move > 0) {
			player.x -= P_Move;
			player.d = LEFT;
		}
		break;
	case RIGHT:
		if (player.x + P_Move < Width - Player_Width) {
			player.x += P_Move;
			player.d = RIGHT;
		}
		break;
	}
}

// ����Ƿ�����
BOOL IfDead() {

	if (player.HP <= 0)
		return TRUE;
	return FALSE;
}