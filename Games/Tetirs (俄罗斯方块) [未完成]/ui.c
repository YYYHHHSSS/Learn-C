#include "Tetirs.h"

#define COLOR_TEXT		RGB(255,255,255)


HWND hWnd = NULL; // ��Ϸ���ھ��
HPEN hPen = NULL; // ���ڻ��Ƴ����Ļ���
// ���ڻ��Ʒ���Ļ�ˢ
HBRUSH hBrush = NULL;
HBRUSH hWhiteBrush = NULL;
HBRUSH hBlackBrush = NULL;
// ���ڵĿ�͸�
#define W 600
#define H 500
// ������ԭ�㣨���Ͻǣ�λ��
#define oX 25
#define oY 25

// ������Ϸ�����Ŀ�͸�
#define sW 300
#define sH 400
// ���飨�����Σ��ı߳�(Length of Side)
#define L 20

// ��Ϸ�����̺߳�����ʵ�ֲ��Ͻ����������ƶ��Ĺ���
DWORD WINAPI Run(LPVOID lpPrarm)
{
	while (!GameOver)
	{
		Sleep(500 - 100 * level);
		if (TryMoveDown(&tetris))
		{
			// �����ƶ�����
			MoveDown(&tetris);
			// ˢ����Ļ�����µ�λ�û��ƶ���˹����
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else
		{
			if (MergeBlock(&tetris))
			{
				InitTetris();
				// �ж��Ƿ�ϲ�һ���в�����
				IfClearRow();
			}
			else
			{
				GameOver = 1;
			}

		}
	}

	return 0;
}

// �Ի�������Ļ��ʻ�ˢ���г�ʼ��
void InitDrawing()
{
	// �������ɫʵ�Ļ���
	hPen = CreatePen(PS_SOLID, 3, RGB(0, 245, 255));
	// �������ɫ��ˢ
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	// ������ɫ������ˢ
	hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
}

// �����ͼ�õ��Ĺ���
void CleanDrawing()
{
	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(hBlackBrush);
}

// ��ʾ��Ϸ��Ϣ
BOOL DrawInfo(HDC hDC)
{
	HFONT hFont, hOldFont;
	hFont = CreateFont(40, 0, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Cursive"));
	if (hOldFont = (HFONT)SelectObject(hDC, hFont))
	{
		SetTextColor(hDC, COLOR_TEXT);
		SetBkMode(hDC, TRANSPARENT); // �����ı�������򱳾�͸��
		CHAR str1[1024];
		wsprintf(str1, "Sorce %d", GetScore());
		TextOut(hDC, sW+70, 150, str1, lstrlen(str1));
		CHAR str2[1024];
		wsprintf(str2, "Level %d", GetLevel());
		TextOut(hDC, sW+70, 220, str2, lstrlen(str2));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hDC, hOldFont);
	}
	return 1;
}

// ���Ƴ�����Ҳ���ǻ���һ�����ο�
// ��ʾ��Ϸ��Χ
BOOL DrawScene(HDC hDC)
{
	// ��������㣬����������Щ�㣬
	// Χ��һ������
	POINT pntArray[5];

	// ��һ��������һ������ͬһλ��
	pntArray[0].x = pntArray[4].x = oX;
	pntArray[0].y = pntArray[4].y = oY;

	pntArray[1].x = sW + oX;
	pntArray[1].y = oY;

	pntArray[2].x = sW + oX;
	pntArray[2].y = sH + oY;

	pntArray[3].x = oX;
	pntArray[3].y = sH + oY;

	HPEN hOldPen = SelectObject(hDC, hPen);

	// ���Ʊ�ʾ��Ϸ�����ľ���
	Polyline(hDC, pntArray, 5);

	// ����ѡ��ԭ���Ļ���
	SelectObject(hDC, hOldPen);
	
	return 1;
}

// ��ָ����λ�ã�row,col������һ������
void DrawBlockRect(HDC hDC, const int row, const int col)
{
	// �����ʾ���鷶Χ�ľ���
	RECT rc;
	rc.left = col*L + oX; // ԭ�����ʼ�������ƫ�Ƶľ���
	rc.right = (col + 1)*L + oX;
	rc.top = row*L + oY;
	rc.bottom = (row + 1)*L + oY;

	// �ð�ɫ��ˢˢ������
	FillRect(hDC, &rc, hWhiteBrush);

	// ��С����һ������
	rc.left += 1;
	rc.right -= 1;
	rc.top += 1;
	rc.bottom -= 1;

	// ����仭ˢ�ڰ�ɫ������ˢ������
	// ����������������˰�ɫ���
	FillRect(hDC, &rc, hBrush);
}

// ���Ƴ����еķ���
void DrawBlock(HDC hDC)
{
	// ����������������
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			// ����з��飬����Ʒ���
			if (blocks[i][j])
			{
				// �ڣ�i,j��λ�û��Ʒ���
				DrawBlockRect(hDC, i, j);
			}
		}
	}
}
// �����ƶ���tetris
void DrawTetris(HDC hDC)
{
	// Ҫ����һ����Ķ���˹����
	// ֻ��Ҫ����������е�С����
	for (int i = 0; i < N; ++i)
	{
		DrawBlockRect(hDC,
			tetris.y[i], // ��
			tetris.x[i]); // ��
	}
}

// ���ƺ�������ӦWM_PAINT��Ϣ
// �����������ڵĻ���
void GamePaint()
{
	PAINTSTRUCT ps;

	// Ϊ���ڻ�ͼ����׼��������
	// ���ͻ�ͼ�йص���Ϣ��䵽һ��PAINTSTRUCT�ṹ��
	HDC hDC = BeginPaint(hWnd, &ps);

	// ��ʾ��Ϸ��Ϣ
	DrawInfo(hDC);
	// ���Ƴ���
	DrawScene(hDC);
	// ���Ƴ����еķ���
	DrawBlock(hDC);
	// �����ƶ��Ķ���˹����
	DrawTetris(hDC);

	// ���ָ�����ڵĻ滭���̽���
	EndPaint(hWnd, &ps);
}

// ���ݲ�ͬ�İ�����Ϣ��������Ӧ�������д���
void OnKeyDown(WPARAM key)
{
	switch (key)
	{
	case VK_RIGHT:  // ���ҷ����
		OnKeyDownRight();
		break;
	case VK_LEFT:  // �������
		OnKeyDownLeft();
		break;
	case VK_DOWN:  // ���·����
		OnKeyDownDown();
		break;
	case VK_UP:
		break;
	case VK_SPACE:
		break;
	default:
		break;
	}
}

// ������Ϣ������
// Ϊ������Ϣָ����Ӧ�����������Ϣ�Ĵ���
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT: // ����
		GamePaint();
		break;
	case WM_KEYDOWN:  
		OnKeyDown(wParam);
		GamePaint();
		break;
	case WM_DESTROY: // �رմ��ڣ���Ϸ����
		GameOver = 1;
		ExitProcess(0);
		break;
	default:
		break;
	};

	// ����Ĭ�ϵĴ�����Ϣ����
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// ע�ᴰ����
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	// ���ô�������
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	// ���ڷ��
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// ������Ϣ��������������ָ�븳ֵ���������
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	// �����ĳ���ʵ������������WinMain()���ݶ���
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // �����ʽ
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);// ����ˢ
	wc.lpszMenuName = NULL;
	// ����������֣��ڴ������ڵ�ʱ�򣬽������������
	// �ҵ���Ӧ�Ĵ�����
	wc.lpszClassName = "Tetirs Game";
	wc.hIconSm = NULL;

	// ע�ᴰ����
	return RegisterClassEx(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	// ����һ���µ���Ϸ����(Windows)
	// �������صĴ��ھ��������window����
	hWnd = CreateWindow(
		"Tetirs Game", // ע�ᴰ����ʱʹ�õ�����
		"Tetirs Game", // ���ڱ���������ʾ�ı���
				  // ָ���������ڵķ��
		WS_OVERLAPPEDWINDOW,
		// �ƶ����ڵĳ�ʼλ��
		CW_USEDEFAULT, CW_USEDEFAULT,
		W, H, // ���ڵĿ�͸�
		NULL, // �޸�����
		NULL, // �޲˵�
		hInstance, // �봰�ڹ����ĳ���ʵ�����
		NULL); // �޸��Ӵ�������

			   // �жϴ��ڴ����Ƿ�ɹ�
	if (!hWnd)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳�
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}

	// ����������ڳɹ�����ʾ����
	ShowWindow(hWnd, nCmdShow);
	// ���£����ƣ�����
	UpdateWindow(hWnd);

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ��ʼ����Ϸ���ںͶ���˹����
	Inite();

	// ע�ᴰ����
	MyRegisterClass(hInstance);

	// ��ʼ��Ӧ�ó��򣬴�������ʾ����
	if (!InitInstance(hInstance, nCmdShow)) return 0;

	// ����һ������
	InitTetris();
	InitDrawing();

	// ������������Ϸ�߳�
	HANDLE hRun = CreateThread(NULL, 0, Run, NULL, 0, NULL);

	// ��Ϣѭ������������Ϸ�����ڼ䶼����
	while (!GameOver)
	{
		MSG msg;
		// ��鴰�ڵ���Ϣ�����Ƿ��������Ϣ
		// ������ڣ�����ȡ���浽msg�ṹ�����
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ���������Ϣת��Ϊ�ַ���Ϣ
			TranslateMessage(&msg);
			// ����Ϣ�ַ�����Ϣ������
			DispatchMessage(&msg);
		}
	}

	// ��Ϣѭ����������ζ�ų��������ִ��������
	CleanDrawing();

	return 0;
}