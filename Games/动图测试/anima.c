#include <windows.h>

HINSTANCE hinst;
HBITMAP hbmpBackground;

// ��������
HBITMAP man[8];
HWND hwndBackground;
HDC mdc, hdc;
int num;

void AnimaPaint(HDC hdc){
	if (num >= 8)
		num = 0;

	SelectObject(mdc, man[num]);
	BitBlt(hdc, 0, 0, 172, 264, mdc, 0, 0, SRCCOPY);
	num++;
}

void Move(HWND hwnd){	
	hdc = GetDC(hwnd);
	mdc = CreateCompatibleDC(hdc);

	TCHAR fileName[20] = { "" };
	for (int i = 1; i < 9; i++){
		wsprintf(fileName, "%d.bmp", i);
		man[i] = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 172, 264, LR_LOADFROMFILE);
	}
	num = 0;
	SetTimer(hwnd, 1, 35, NULL);

	AnimaPaint(hdc);
}


// �ص�����
LONG CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
	case WM_CREATE:
		break;
	case WM_PAINT:
		Move(hwnd);
		break;
	case WM_KEYDOWN:
		break;
	case WM_DESTROY:
		ExitProcess(0);
		break;
	case WM_TIMER:
		AnimaPaint(hdc);
		break;
	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ���
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "MainMenu";
	wc.lpszClassName = "MainWClass";
	if (!RegisterClass(&wc)){
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}

	hwnd = CreateWindow(
		"MainWClass",			// �����������������Ѿ�ע���˵Ĵ�����
		"Test",		// title-bar string 
		WS_OVERLAPPEDWINDOW,	// ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd){
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}

	hbmpBackground = hwnd;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1){
		TranslateMessage(&msg); // ���������Ϣת��Ϊ�ַ���Ϣ
		DispatchMessage(&msg); // ��Ϣ���ַ����ص�����
	}
	return msg.wParam;
}