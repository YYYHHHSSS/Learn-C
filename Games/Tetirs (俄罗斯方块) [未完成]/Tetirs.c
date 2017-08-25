#include "Tetirs.h"

//��ʼ������
int score = 0;
int level = 0;
BOOL GameOver = 0;
int N = 4;
int blocks[20][15];

void Inite()
{
	int i, j;

	// �������������
	// ��Ҫʹ�����������ʳ���λ�õ�
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft); // ��ȡϵͳʱ��
	srand(ft.dwLowDateTime);

	// ��ʼ����Ϸ����
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
			blocks[i][j] = 0;
	}

	// "I"�εĶ���˹����
	for (i = 0; i < N; ++i)
	{
		option[0].x[i] = 1;
		option[0].y[i] = -i;
	}

	// "L"�εĶ���˹����
	option[1] = option[0];
	option[1].x[N - 1] = 2;
	option[1].y[N - 1] = 0;

	// "��"�εĶ���˹����
	option[2] = option[0];
	option[2].x[N - 1] = 2;
	option[2].x[N - 2] = 2;
	option[2].y[N - 1] = -1;
	option[2].y[N - 2] = 0;

	// "͹"�εĶ���˹����
	option[3] = option[1];
	option[3].x[1] = 2;
	option[3].x[2] = 2;
	option[3].x[N - 1] = 3;
	option[3].y[1] = 0;
	option[3].y[2] = -1;

	// "Z"�εĶ���˹����
	option[4] = option[3];
	option[4].y[0] = -1;
}

// ���ػ���
int GetScore() { return score; }

// ����level
int GetLevel() { return level; }

// ��tetris���г�ʼ����
void InitTetris()
{
	// �������һ������˹����
	int i = rand() % 5;
	tetris = option[i];
}
// ��tetris�����ƶ�
void MoveDown(Tetris* t)
{
	// �������tetris�е�С����
	for (int i = 0; i < N; ++i)
	{
		// ��ÿ�������x�����1��ʵ���ƶ�
		t->y[i] += 1;
	}
}

// �ж��Ƿ���Լ��������ƶ�����˹����
BOOL TryMoveDown(Tetris* t)
{
	// ����һ����ʱ�Ķ���˹����
	Tetris tmp = *t;
	// �����ƶ���ʱ����˹����
	MoveDown(&tmp);
	// �ж��ƶ���ķ����Ƿ񳬳��߽�
	// �Լ������˳����е���������
	for (int i = 0; i < N; ++i)
	{
		// �ƶ������λ��
		int row = tmp.y[i];
		int col = tmp.x[i];
		if (row >= ROW) // �Ƿ񳬳��±߽�
		{
			return 0;
		}
		// �ж��Ƿ����������еķ���
		// �����ж��ƶ����λ���Ƿ��ڳ����ڲ�
		if (row >= 0 && row < ROW
			&& col >= 0 && col < COL
			// Ȼ���ж����λ���Ƿ��Ѿ��з���
			&& blocks[row][col])
		{
			// ����Ѿ��з��飬�ƶ����ɹ�
			return 0;
		}
	}

	// ���������ƶ�
	return 1;
}

// ���ƶ����ײ��Ķ���˹����ϲ��������ķ�����
BOOL MergeBlock(Tetris* t)
{
	for (int i = 0; i < N; ++i)
	{
		// ��������������������޷��ϲ�
		if (t->y[i] < 0)
		{
			return 0;
		}
		// �������ж�Ӧ��λ������Ϊ1��
		// ��������ϲ����˳�����
		blocks[t->y[i]][t->x[i]] = 1;
	}
	// ���غϲ��ɹ�
	return 1;
}

// �����ƶ�
void MoveRight(Tetris* t)
{
	for (int i = 0; i < N; ++i)
	{
		t->x[i] += 1;
	}
}
// ��ײ��⣬�ж��Ƿ���������ƶ�
BOOL TryMoveRight(Tetris* t)
{
	Tetris tmp = *t;
	MoveRight(&tmp);

	for (int i = 0; i < N; ++i)
	{
		if (tmp.x[i] >= COL || blocks[tmp.y[i]][tmp.x[i]])
		{
			return 0;
		}
	}

	return 1;
}
// �������Ұ���������Ϣ
void OnKeyDownRight()
{
	// �ж��Ƿ���������ƶ�
	if (TryMoveRight(&tetris))
	{
		// ������ԣ������ƶ�
		MoveRight(&tetris);
	}
}

// �����ƶ�
void MoveLeft(Tetris* t)
{
	for (int i = 0; i < N; ++i)
	{
		t->x[i] -= 1;
	}
}
// ��ײ��⣬�ж��Ƿ���������ƶ�
BOOL TryMoveLeft(Tetris* t)
{
	Tetris tmp = *t;
	MoveLeft(&tmp);

	for (int i = 0; i < N; ++i)
	{
		if (tmp.x[i] < 0 || blocks[tmp.y[i]][tmp.x[i]])
		{
			return 0;
		}
	}

	return 1;
}
// �������󰴼�������Ϣ
void OnKeyDownLeft()
{
	if (TryMoveLeft(&tetris))
	{
		MoveLeft(&tetris);
	}
}

// ���¼����ƶ�
void MoveDownFast(Tetris* t)
{
	for (int i = 0; i < N; ++i)
	{
		t->y[i] += 1;
	}
}
void OnKeyDownDown()
{
	if (TryMoveDown(&tetris))
	{
		MoveDownFast(&tetris);
	}
}

// ��ת
void OnKeyDownUp()
{

}

//ˢ�·���
void IfClearRow()
{
	int i, j;
	BOOL flag;
	// ������������
	for (i = 0; i < ROW; i++)
	{
		flag = 1;
		for (j = 0; j < COL; j++)
		{
			if (blocks[i][j] == 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			Update(i);
			score += 10;
			if (score >= 100)
				level++;
		}
	}
}

void Update(int i)
{
	int j;
	for (; i > 0; i--)
	{
		for (j = 0; j < COL; j++)
			blocks[i][j] = blocks[i - 1][j];
	}
}