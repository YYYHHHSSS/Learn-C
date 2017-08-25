#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <Windows.h>
#define DEAL	50	/*�������״���*/
struct Date
{
	int da_year;  //��
	int da_mon;  //��
	int da_day;  //��
};
struct Time
{
	int ti_hour;   //Сʱ
	int ti_min;   //����
	int ti_sec;    //��
};
struct deal
{
	Date dt;						/*ÿ�ʽ��׵�����*/
	Time ti;						/*ÿ�ʽ��׵�ʱ��*/
	double earning;						/*ÿ�ʽ��׵�������*/
	double payout;						/*ÿ�ʽ��׵�֧�����*/
};
typedef struct deal FINANCE;
FINANCE person[DEAL] = { 0 };    //����û�ÿ�ʵĽ�����Ϣ

void getdate(Date *pd);//��ʵ�֣�������ʾ����ȡϵͳ���ڣ�����pd��ָ��Date�ṹ����
void gettime(Time *pt);// ��ʵ�֣�������ʾ����ȡϵͳʱ�䣬����pt��ָ��Time�ṹ����
void GetDateTime(FINANCE *per); //����getdate��gettime��������ȡ��ʱ�����ڴ���per��ָ�Ľṹ�������
void Menu();  //��ʾϵͳ�˵�
char bioskey(); //�����û�����Ĳ˵�����
void InputOneDeal(FINANCE *per);  //ִ�в˵�����1������һ�ʽ��ף�����ṹ��per��ָ�Ľṹ������С�ע�⵱����Ϊ������ʱ�����earning�У�����Ϊ������ʱ�����payout�С�
float Balance(FINANCE *per);  //�����˻������˻�person�����е�����������֧��֮�
void OneYearBalance(FINANCE *per, int year); //��ӡĳһ��Ľ�����Ϣͳ��
void PrintBalance(FINANCE *per);  //ִ�в˵�����2����ӡ������ݵ����н�����Ϣ
void PrintOneYear(FINANCE *per);//ִ�в˵�����3����ӡĳһ������н�����Ϣ���������꽻����ϸ������OneYearBalance�����������ͳ��

int main()
{
	char key;
	int i;
	i = 0;
	while (1)
	{
		Menu();
		key = bioskey();
		fflush(stdin);   //��ջ�����
		switch (key)
		{
		case '1':  InputOneDeal(person + i);
			i++;
			break;
		case '2':  PrintBalance(person);
			break;
		case '3':  PrintOneYear(person);
			break;
		case '4':  exit(0);
		default:  break;
		}
	}
}
//��ȡϵͳ���ڣ�����pd��ָ��Date�ṹ����
void getdate(Date *pd)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	pd->da_day = st.wDay;
	pd->da_mon = st.wMonth;
	pd->da_year = st.wYear;
}
//��ȡϵͳʱ�䣬����pt��ָ��Time�ṹ����
void gettime(Time *pt)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	pt->ti_hour = st.wHour;
	pt->ti_min = st.wMinute;
	pt->ti_sec = st.wSecond;
}
void GetDateTime(FINANCE *per)
{
	getdate(&(*per).dt);
	gettime(&(*per).ti);
}//����getdate��gettime��������ȡ��ʱ�����ڴ���per��ָ�Ľṹ�������
void Menu()
{
	printf("1.Input One deal\n");
	printf("2.Print All the Balance\n");
	printf("3.Print One year Balance\n");
	printf("4.Exit to DOS\n");
}//��ʾϵͳ�˵�
char bioskey() 
{
	char c;
	char ch;
	scanf("%c", &c);
	while ((ch = getchar()) != '\n'&&ch != EOF);
	return c;
} //�����û�����Ĳ˵�����
void InputOneDeal(FINANCE *per) 
{
	float x;
    GetDateTime(per);
	printf("Please input one deal <+/->:\n");
	printf("%d/%d/%d   %02d:%02d:%02d  :", (*per).dt.da_year, (*per).dt.da_mon, (*per).dt.da_day, (*per).ti.ti_hour, (*per).ti.ti_min, (*per).ti.ti_sec);
	scanf("%f", &x);
	char ch;

	while ((ch = getchar()) != '\n'&&ch != EOF);
	if (x > 0)
		(*per).earning = x;
	else
		(*per).payout = x;
}  //ִ�в˵�����1������һ�ʽ��ף�����ṹ��per��ָ�Ľṹ������С�ע�⵱����Ϊ������ʱ�����earning�У�����Ϊ������ʱ�����payout�С�
float Balance(FINANCE *per) 
{
	float sum = 0;
	int i;
	for (i = 0; per[i].earning != 0 || per[i].payout != 0; i++)
	{
		sum = sum + per[i].earning + per[i].payout;
	}
	return sum;
}  //�����˻������˻�person�����е�����������֧��֮�
void OneYearBalance(FINANCE *per, int year) 
{
	int i, flag = 0;
	float payout, earning;
	payout = earning = 0;
	for (i = 0; per[i].dt.da_year == year; i++)
	{
		payout += per[i].payout;
		earning += per[i].earning;
	}
	printf("\n\nparam of %d :\n", year);
	printf("%15s%20s%15s\n", "Sum of earning", "Sum of payout", "Balance");
	if (payout == 0 && earning == 0)
		printf("%15.2f%20.2f%15.2f\n", 0, 0, 0);
	else
		printf("%15.2f%20.2f%15.2f\n", earning, payout, Balance(per));
} //��ӡĳһ��Ľ�����Ϣͳ��
void PrintBalance(FINANCE *per) 
{
	int i;
	printf("%6s%12s%15s%10s%12s\n", "Date", "Time", "Earning", "Payout", "Balance");
	for (i = 0; i < 60; i++)
		printf("-");
	printf("\n");
	for (i = 0; per[i].dt.da_year !=0; i++)
		printf("%d/%d/%d   %d:%d:%d%10.2f  %10.2f\n", per[i].dt.da_year, per[i].dt.da_mon, per[i].dt.da_day, per[i].ti.ti_hour, per[i].ti.ti_min, per[i].ti.ti_sec, per[i].earning, per[i].payout);
	for (i = 0; i < 60; i++)
		printf("-");
	printf("\n%55.2f\n", Balance(per));
}  //ִ�в˵�����2����ӡ������ݵ����н�����Ϣ
void PrintOneYear(FINANCE *per) 
{
	int i, x;
	printf("Please Input one year :");
	scanf("%d", &x);
	char ch;
	while ((ch = getchar()) != '\n'&&ch != EOF);
	printf("%6s%12s%15s%10s%12s\n", "Date", "Time", "Earning", "Payout", "Balance");
	for (i = 0; i < 60; i++)
		printf("-");
	printf("\n");
	for (i = 0; per[i].dt.da_year == x; i++)
		printf("%d/%d/%d   %d:%d:%d%10.2f  %10.2f\n", per[i].dt.da_year, per[i].dt.da_mon, per[i].dt.da_day, per[i].ti.ti_hour, per[i].ti.ti_min, per[i].ti.ti_sec, per[i].earning, per[i].payout);
	for (i = 0; i < 60; i++)
		printf("-");
	OneYearBalance(per, x);
}//ִ�в˵�����3����ӡĳһ������н�����Ϣ���������꽻����ϸ������OneYearBalance�����������ͳ��

