#include  <stdio.h>
#include<time.h>

struct clock
{
	int hour;
	int minute;
	int second;
};
typedef struct clock CLOCK;

/*�������ܣ�ʱ���֡���ʱ��ĸ���
����������ָ��CLOCK�ṹ�������ָ��t����ʾʱ���֡���ʱ��
��������ֵ��	��
*/
void Update(CLOCK *t)
{
	t->second++;
	if (t->second == 60) 	/*��secondֵΪ����ʾ�ѹ�һ���ӣ���minuteֵ��*/
	{
		t->second = 0;
		t->minute++;
	}
	if (t->minute == 60)   	/*��minuteֵΪ����ʾ�ѹ�һСʱ����hourֵ��*/
	{
		t->minute = 0;
		t->hour++;
	}
	if (t->hour == 24)     	/*��hourֵΪ����hourֵ�ӿ�ʼ��ʱ*/
	{
		t->hour = 0;
	}
}

/*�������ܣ�ʱ���֡���ʱ�����ʾ
����������ָ��CLOCK�ṹ�������ָ��t����ʾʱ���֡���ʱ��
��������ֵ��	��
*/
void Display(CLOCK *t)
{
	printf("%02d:%02d:%02d\r", t->hour, t->minute, t->second);
}

/*�������ܣ�ģ���ӳ����ʱ��
������������
��������ֵ��	��
*/
void Delay(void)
{
	long t;
	/*time_t currentTime;
	currentTime = time(NULL);
	while( time(NULL) < currentTime + 1);*/

	for (t = 0; t<500000000; t++)
	{
		/*ѭ����Ϊ������ѭ��������ʱ����*/
	}
}

int main()
{
	long i;
	CLOCK myclock;

	myclock.hour = myclock.minute = myclock.second = 0;
	for (i = 0; i<100000; i++)    		/*����ѭ���ṹ������ʱ�����е�ʱ��*/
	{
		Update(&myclock);          	/*ʱ�Ӹ���*/
		Display(&myclock);          	/*ʱ����ʾ*/
		Delay();                     	/*ģ����ʱ��*/
	}
}
