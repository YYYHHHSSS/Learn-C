#pragma once
#ifndef _OPERATION_H
#define _OPERATION_H

#include <math.h>
#include "player.h"

// �����ƶ�
void ArmyMove(AllType *a);
void MoveArmy();

// ���﹥��
void ArmyAttack();
BOOL Army_yMeet(AllType *a);

// ��ҹ���
BOOL yMeetArmy(AllType *a);
BOOL xMeetArmy(AllType *a);
void AttackArmy();

// ��Ҵ���
BOOL yMeetBig(AllType *a);
BOOL xMeetBig(AllType *a);
void BigAttack();
void Clearbehit();


#endif // !_OPERATION_H