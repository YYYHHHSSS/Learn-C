#include<stdio.h>

int main()
{
	int x, y, flag;
	int a[7] = {3, 10, 20, 25, 30, 35, 45}, b[7] = {0, 105, 555, 1005, 2775, 5505, 13505};
	double sum, del, num;
	do
	{
		scanf("%d %d", &x, &y);
	} while (x < 0 || y < 0);
	num = x - y - 3500;
	if (num <= 0)
		printf("��������ɸ�������˰\n");
	else
	{
		if (num <= 1500)
			flag = 0;
		else if (num > 1500 & num <= 4500)
			flag = 1;
		else if (num > 4500 & num <= 9000)
			flag = 2;
		else if (num > 9000 & num <= 35000)
			flag = 3;
		else if (num > 35000 & num <= 55000)
			flag = 4;
		else if (num > 55000 & num <= 80000)
			flag = 5;
		else
			flag = 6;
		del = num * a[flag] / 100 - b[flag];
		sum = x - y - del;
		printf("Ӧ��˰���ö�:%.2f\n����˰��:%d%%\n����۳���:%d\nӦ��˰��:%.2f\nʵ������:%.2f\n", num, a[flag], b[flag], del, sum);
	}
}