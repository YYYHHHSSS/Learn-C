#ifndef _TETIRS_H
#define _TETIRS_H

#include <Windows.h>

// �����ʾ����˹����Ľṹ��Tetris
// ÿ������˹�������ĸ�С���飬
// ��������ṹ���¼4��λ����Ϣ��
// ���磬(x[0],y[0])���ǵ�һ���������Ϣ
typedef struct
{
	int x[4];  // ��
	int y[4];  // ��
} Tetris;

// ÿ����Ķ���˹�����е�С������
extern int N;

// ��Ϸ�Ƿ����
extern BOOL GameOver;

//��ѡ�Ķ���˹����
Tetris option[5];
// ��Ϸ�������ƶ��Ķ���˹����
Tetris tetris;

// ��Ϸ���������ɷ�����к���
#define COL 15
#define ROW 20  

// ��¼�����еķ��������, 0��ʾ�޷��飬1��ʾ�з���
extern int blocks[][15];

// ��ʱ��ID
#define TIMER_ID 12340
// �ж���Ϸ�Ƿ�ﵽ��������
#define IS_SPEEDUP(s) (s % dwOneLevelScores) == 0


// ��ʱ����ʱ���
DWORD dwTimerElapse;
// ÿ���һ������ʱ��ʱ���������̵ı���
DOUBLE dbLevelSpeedupRatio;
// �˱�����ʾ���ٸ���������һ������
DWORD dwOneLevelScores;

// ����Ʒ֣���ʼΪ0
extern int score;
// ���漶�𣬳�ʼΪ0
extern int level;


int GetScore();
int GetLevel();
void InitTetris();
void MoveDown(Tetris* t);
BOOL TryMoveDown(Tetris* t);
BOOL MergeBlock(Tetris* t);
void MoveRight(Tetris* t);
BOOL TryMoveRight(Tetris* t);
void OnKeyDownRight();
void MoveLeft(Tetris* t);
BOOL TryMoveLeft(Tetris* t);
void OnKeyDownLeft();
void MoveDownFast(Tetris* t);
void OnKeyDownDown();
void IfClearRow();
void Update();

#endif // !TETIRS_H