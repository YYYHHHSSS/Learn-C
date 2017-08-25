#include <windows.h>
#pragma comment(lib,"Msimg32.lib")
#pragma comment(lib,"winmm.lib") // �������������ӿ�  

#define WINDOW_WIDTH    540
#define WINDOW_HEIGHT   560
#define WINDOW_TITLE    "������"

int map[15][15];
int NowPlayer;		// ��ǰ���֣��ڻ�ף�

int g_nx;	// ��ǰ�������
int g_ny;

int g_mx;	// ��ǰ��������Ӧmap��λ��
int g_my;

HDC g_hdc = NULL, g_mdc = NULL, g_tdc = NULL; // �豸DC 
HBITMAP g_hmap = NULL;	   // ���̾��
HBITMAP g_hch = NULL;	   // ������
HBITMAP g_hch2 = NULL;	   // ������

// ��������
LONG CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL Game_Init(HWND hwnd);
VOID Game_Paint(HWND hwnd);
BOOL Game_CleanUp(HWND hwnd);
VOID MouseMove(LPARAM lParam);
int WinOrNot(int x, int y);

// �������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	WNDCLASSEX wndClass = { 0 }; // ���崰����
	wndClass.cbSize = sizeof(WNDCLASSEX); // �������ֽڴ�С
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // ������ʽ
	wndClass.lpfnWndProc = WndProc; // ���ڹ��̺���ָ��
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance; // ���ھ��
	wndClass.hIcon = LoadImage(NULL, "icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); // ���ش���ͼ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);// ���ش��ڹ��
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ��ɫˢ��ˢ��Ļ
	wndClass.lpszClassName = "Five";// ����������
	wndClass.lpszMenuName = NULL;// �����˵�

	if (!RegisterClassEx(&wndClass))// ע�ᴰ��
		return -1;

	// ��������
	HWND hwnd = CreateWindow("Five", WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	// �����ƶ�
	MoveWindow(hwnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, 1);

	// ������ʾ
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	// ��Ϸ��Դ��ʼ��
	if (!Game_Init(hwnd)){
		MessageBox(hwnd, "��Դ��ʼ��ʧ��", "��ʾ", 0);
		return FALSE;
	}

	// ��Ϣѭ��
	MSG msg = { 0 };
	while (msg.message != WM_QUIT){
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterClass("Five", wndClass.hInstance);
	return 0;
}

// �ص�����
LONG CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	//PAINTSTRUCT paintStruct;

	switch (message){
	case WM_TIMER:						// ��ʱ����Ϣ
		Game_Paint(hwnd);                // ����Game_Paint�����������д��ڻ�ͼ
		break;

		//case WM_PAINT:
		//	g_hdc=BeginPaint( hwnd,&paintStruct);
		//	Game_Paint( hwnd);
		//	EndPaint(hwnd,&paintStruct);
		//	ValidateRect(hwnd,NULL);  //ˢ�½���
		//	break;

	case WM_KEYDOWN:
		switch (wParam){
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		default:
			MessageBox(NULL, "ESC���˳�����", "��ʾ", 0);
			break;
		}
		break;

	case WM_LBUTTONDOWN:	// ����������
		if (NowPlayer == 1){
			if (map[g_mx][g_my] == 0){
				map[g_mx][g_my] = 1;
				WinOrNot(g_mx, g_my);
				PlaySound(L"MC.wav", NULL, SND_FILENAME | SND_ASYNC);
				NowPlayer = 2;
			}
			else
				PlaySound(L"Close.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (NowPlayer == 2){
			if (map[g_mx][g_my] == 0){
				map[g_mx][g_my] = 2;
				WinOrNot(g_mx, g_my);
				PlaySound(L"MC.wav", NULL, SND_FILENAME | SND_ASYNC);
				NowPlayer = 1;
			}
			else
				PlaySound(L"Close.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		break;
	case WM_MOUSEMOVE:		// ����ƶ�
		MouseMove(lParam);		// ��ȡ��ǰ��Ӧ��map����
		break;
	case WM_DESTROY:
		Game_CleanUp(hwnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

// ��Ϸ��ʼ��
BOOL Game_Init(HWND hwnd){
	HBITMAP bmp;// ����λͼ����

	g_hdc = GetDC(hwnd);
	g_hmap = (HBITMAP)LoadImage(NULL, "����.bmp", IMAGE_BITMAP, 535, 535, LR_LOADFROMFILE);  // 22,22Ϊ���̵�һ����
	g_hch = (HBITMAP)LoadImage(NULL, "����.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	g_hch2 = (HBITMAP)LoadImage(NULL, "����.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	g_mdc = CreateCompatibleDC(g_hdc);
	g_tdc = CreateCompatibleDC(g_hdc);
	bmp = CreateCompatibleBitmap(g_hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(g_mdc, bmp);

	// ��ʼ������
	for (int x = 0; x <= 14; x++){
		for (int y = 0; y <= 14; y++){
			map[x][y] = 0;
		}
	}
	SetTimer(hwnd, 1, 15, NULL); // 90���뷢��һ����Ϣ
	NowPlayer = 1;
	Game_Paint(hwnd);
	//ReleaseDC(hwnd,g_hdc);

	return TRUE;
}

// ��Ϸ������ˢ��
VOID Game_Paint(HWND hwnd){
	// ������
	SelectObject(g_tdc, g_hmap);
	BitBlt(g_mdc, 0, 0, 535, 535, g_tdc, 0, 0, SRCCOPY);

	// 1Ϊ���壬2Ϊ����
	for (int x = 0; x <= 14; ++x){
		for (int y = 0; y <= 14; ++y){
			if (map[x][y] == 1){
				SelectObject(g_tdc, g_hch);
				TransparentBlt(g_mdc, x * 35 + 22 - 16, y * 35 + 22 - 16, 32, 32, g_tdc, 0, 0, 32, 32, RGB(255, 255, 255));
			}
			else if (map[x][y] == 2){
				SelectObject(g_tdc, g_hch2);
				TransparentBlt(g_mdc, x * 35 + 22 - 16, y * 35 + 22 - 16, 32, 32, g_tdc, 0, 0, 32, 32, RGB(255, 255, 255));
			}
		}
	}


	// �ڵ�ǰ���λ�û������壬���������ƶ����ı�
	if (NowPlayer == 1){
		SelectObject(g_tdc, g_hch);
		TransparentBlt(g_mdc, g_mx * 35 + 22 - 16, g_my * 35 + 22 - 16, 32, 32, g_tdc, 0, 0, 32, 32, RGB(255, 255, 255));
	}
	else if (NowPlayer == 2){
		SelectObject(g_tdc, g_hch2);
		TransparentBlt(g_mdc, g_mx * 35 + 22 - 16, g_my * 35 + 22 - 16, 32, 32, g_tdc, 0, 0, 32, 32, RGB(255, 255, 255));
	}
	BitBlt(g_hdc, 0, 0, 540, 560, g_mdc, 0, 0, SRCCOPY);
}
BOOL Game_CleanUp(HWND hwnd){
	KillTimer(hwnd, 1);   // ɾ���������Ķ�ʱ��  
	DeleteObject(g_hmap);
	DeleteObject(g_hch);
	DeleteObject(g_hch2);
	DeleteDC(g_mdc);
	DeleteDC(g_hdc);
	ReleaseDC(hwnd, g_hdc);

	return TRUE;
}

// ����ƶ� �������������ϵ�λ��
VOID MouseMove(LPARAM lParam){
	g_nx = LOWORD(lParam);
	g_ny = HIWORD(lParam);
	for (int x = 0; x <= 14; ++x){
		for (int y = 0; y <= 14; ++y){
			if (g_nx >= x * 35 + 22 - 16 && g_nx <= x * 35 + 22 + 16 && g_ny >= y * 35 + 22 - 16 && g_ny <= y * 35 + 22 + 16){
				g_mx = x;
				g_my = y;
			}
		}
	}
}

// �ж���Ӯ
int WinOrNot(int x, int y){
	int tx = 0, ty = 0;
	int playernum;
	int i;
	int cnum = 0;

	playernum = map[x][y];

	//һ�����޼��
	for (i = 1; i <= 4; i++){
		//��һ����
		if (x + i <= 14 && y - i >= 0 && map[x + i][y - i] == playernum){
			cnum++;
		}
		else
			break;
		//MessageBox(NULL, "�����Ƿ�break��һ����", "��ʾ",0);
	}

	for (i = 1; i <= 4; i++){
		//��������
		if (x - i >= 0 && y + i <= 14 && map[x - i][y + i] == playernum){
			cnum++;
		}
		else
			break;
		//MessageBox(NULL, "�����Ƿ�break��������", "��ʾ",0);
	}
	if (cnum == 4){
		cnum = 0;
		if (playernum == 1){
			MessageBox(NULL, "����Ӯ��", "��ʾ", 0);
			//��ʼ������
			for (tx = 0; tx <= 14; tx++){
				for (ty = 0; ty <= 14; ty++){
					map[tx][ty] = 0;
				}
			}
			NowPlayer = 1;
		}
		else{
			MessageBox(NULL, "����Ӯ��", "��ʾ", 0);
			//��ʼ������
			for (tx = 0; tx <= 14; tx++){
				for (ty = 0; ty <= 14; ty++){
					map[tx][ty] = 0;
				}
			}
			NowPlayer = 1;
		}
		return 0;
	}
	else
		cnum = 0;

	//���������ж�
	for (i = 1; i <= 4; i++){
		//��������
		if (x - i >= 0 && y - i >= 0 && map[x - i][y - i] == playernum){
			cnum++;
		}
		else
			break;
		//MessageBox(NULL, "�����Ƿ�break��������", "��ʾ",0);
	}

	for (i = 1; i <= 4; i++){
		//�ڶ�����
		if (x + i <= 14 && y + i <= 14 && map[x + i][y + i] == playernum){
			cnum++;
		}
		else
			break;
		//MessageBox(NULL, "�����Ƿ�break�ڶ�����", "��ʾ",0);
	}
	if (cnum == 4){
		cnum = 0;
		if (playernum == 1)
			MessageBox(NULL, "����Ӯ��", "��ʾ", 0);
		else
			MessageBox(NULL, "����Ӯ��", "��ʾ", 0);
		//MessageBox(NULL, "Ӯ�ڶ�������", "��ʾ",0);
		return 0;
	}
	else
		cnum = 0;

	//��ֱ�ж�
	for (i = 1; i <= 4; i++){
		//����
		if (y - i >= 0 && map[x][y - i] == playernum){
			cnum++;
		}
		else
			break;
		//MessageBox(NULL, "�����Ƿ�break��", "��ʾ",0);
	}

	for (i = 1; i <= 4; i++){
		//����
		if (y + i <= 14 && map[x][y + i] == playernum){
			cnum++;
		}
		else
			break;
		//MessageBox(NULL, "�����Ƿ�break��", "��ʾ",0);
	}
	if (cnum == 4){
		cnum = 0;
		if (playernum == 1)
			MessageBox(NULL, "����Ӯ��", "��ʾ", 0);
		else
			MessageBox(NULL, "����Ӯ��", "��ʾ", 0);
		//MessageBox(NULL, "Ӯ�ڴ�ֱ�ж�", "��ʾ",0);
		return 0;
	}
	else
		cnum = 0;


	// ˮƽ�ж�
	for (i = 1; i <= 4; i++){
		// ����
		if (x - i >= 0 && map[x - i][y] == playernum){
			cnum++;
		}
		else
			break;
		//MessageBox(NULL, "�����Ƿ�break��", "��ʾ", 0);
	}

	for (i = 1; i <= 4; i++){
		// ����
		if (x + i <= 14 && map[x + i][y] == playernum){
			cnum++;
		}
		else
			break;
		//MessageBox(NULL, "�����Ƿ�break��", "��ʾ", 0);
	}
	if (cnum == 4){
		cnum = 0;
		if (playernum == 1)
			MessageBox(NULL, "����Ӯ��", "��ʾ", 0);
		else
			MessageBox(NULL, "����Ӯ��", "��ʾ", 0);
		//MessageBox(NULL, "Ӯ��ˮƽ�ж�", "��ʾ", 0);
		return 0;
	}
	else
		cnum = 0;
}