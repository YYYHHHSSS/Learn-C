#include<stdio.h>
typedef   struct  date{	int   month;	int   day;	int   year;}DATE;
struct  Employee{	char name[20];	int  num;	DATE birthday;};
void Input(Employee *p, int n);  //nΪԱ��������pΪָ��ṹ�������ָ��
int main()
{
	struct  Employee emp[100];	int n, i;	scanf("%d", &n);	for (i = 0; i < n; i++)		scanf("%s %d %d %d %d", emp[i].name, &emp[i].num, &emp[i].birthday.year, &emp[i].birthday.month, &emp[i].birthday.day);
	Input(emp, n);
	return 0;
}
void Input(Employee *p, int n)
{
	int a, b, i, flag = 0;
	scanf("%d %d", &a, &b);
	for (i = 0; i < n; i++)
	{
		if (p[i].birthday.month == a&& p[i].birthday.day == b)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		printf("%d��%d�չ����յ��У�\n", a, b);
		printf("       ����    ����    ����(��   ��   ��)\n");
		for (i = 0; i < n; i++)
		{
			if (p[i].birthday.month == a&& p[i].birthday.day == b)
				printf("%8s%10d%14d%4d%4d\n", p[i].name, p[i].num, p[i].birthday.year, p[i].birthday.month, p[i].birthday.day);
		}
	}
	else
		printf("Not Found");
}