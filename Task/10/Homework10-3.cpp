#include <stdio.h>

#define ARR_SIZE 40

int FindMax(int score[], long num[], int n, long *pMaxNum);

int main()
{
	int score[ARR_SIZE], maxScore, n, i;
	long num[ARR_SIZE], maxNum;

	// printf("Please enter total number:");
	scanf("%d", &n); /*�Ӽ�������ѧ������n*/

					 // printf("Please enter the number and score:\n");
	for (i = 0; i<n; i++) /*�ֱ��Գ����ͺ����͸�ʽ����ѧ����ѧ�źͳɼ�*/
	{
		scanf("%ld%d", &num[i], &score[i]);
	}

	maxScore = FindMax(score, num, n, &maxNum); /*������߷ּ�ѧ��ѧ��*/

	printf("maxScore = %d, maxNum =%ld", maxScore, maxNum);

	return 0;
}
int FindMax(int score[], long num[], int n, long *pMaxNum)
{
	int i, j;
	j = score[0];
	*pMaxNum = num[0];
	for (i = 1; i < n; i++)
	{
		if (j < score[i])
		{
			j = score[i];
			*pMaxNum = num[i];
		}
	}
	return  j;
}