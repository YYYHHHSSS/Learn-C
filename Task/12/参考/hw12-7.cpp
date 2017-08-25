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
FINANCE person[DEAL]={0};    //����û�ÿ�ʵĽ�����Ϣ

void getdate(Date *pd);//��ȡϵͳ���ڣ�����pd��ָ��Date�ṹ����
void gettime(Time *pt);//��ȡϵͳʱ�䣬����pt��ָ��Time�ṹ����
void GetDateTime(FINANCE *per); //����getdate��gettime��������ȡ��ʱ�����ڴ���per��ָ�Ľṹ��������
void Menu();  //��ʾϵͳ�˵�
char bioskey(); //�����û�����Ĳ˵�����
void InputOneDeal(FINANCE *per);  //ִ�в˵�����1������һ�ʽ��ף�����ṹ��������
float Balance(FINANCE *per);  //�����˻������
void OneYearBalance(FINANCE *per,int year); //��ӡĳһ��Ľ�����Ϣͳ��
void PrintBalance(FINANCE *per);  //ִ�в˵�����2����ӡ������ݵ����н�����Ϣ
void PrintOneYear(FINANCE *per);//ִ�в˵�����3����ӡĳһ��Ľ�����Ϣ���������꽻����ϸ������ͳ��

int main()
{
	char key;
	int i;

	i = 0;

	while(1)
	{
		Menu();
		key=bioskey();
		fflush(stdin);   //��ջ�����
 		switch(key)
		{
		case '1':  InputOneDeal(person+i);
			i++;
			break;
		case '2':  PrintBalance(person);
			break;
		case '3':  PrintOneYear(person);
			break;
		case '4':  exit(0);
		default :  break;
		}
	}
}

//��ȡϵͳ���ڣ�����pd��ָ��Date�ṹ����
void getdate(Date *pd)  
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	pd->da_day=st.wDay;
	pd->da_mon=st.wMonth;
	pd->da_year=st.wYear;
}
//��ȡϵͳʱ�䣬����pt��ָ��Time�ṹ����
void gettime(Time *pt)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	pt->ti_hour=st.wHour;
	pt->ti_min=st.wMinute;
	pt->ti_sec=st.wSecond;
}
/*	�������ܣ���ü������ϵͳ���ڡ�ʱ��
�����������ṹ��ָ�����per������ָ��ṹ�������ָ��
��������ֵ����
*/
void GetDateTime(FINANCE *per)
{
	getdate(&per->dt);
	printf("%d/%02d/%02d  ",per->dt.da_year,per->dt.da_mon,per->dt.da_day);

	gettime(&per->ti);
	printf("%02d:%02d:%02d :",per->ti.ti_hour,per->ti.ti_min,per->ti.ti_sec);
}
/*	�������ܣ�ÿһ�ʽ�������ģ��
�����������ṹ��ָ�����per������ָ��ṹ�������ָ��
��������ֵ����
*/
void InputOneDeal(FINANCE *per)
{
	char string[10];

	printf("Please input one deal (+/-):\n");
	GetDateTime(per);

	scanf("%s",&string);
	if(string[0] == '-')
		per->payout = atof(string);  //atof�������ڽ�һ���ַ���ת��Ϊ��Ӧ�����֣��罫"-475.67"ת��Ϊ-475.67
	else
		per->earning = atof(string);
}
/*	�������ܣ��������ϵ����
�����������ṹ��ָ�����per������ָ��ṹ�������ָ��
��������ֵ���������
*/
float Balance(FINANCE *per)
{
	int i;
	double sum1 = 0.0,sum2 = 0.0;

	for(i=0;i<DEAL;i++)
	{
		sum1 += (per+i)->earning;
		sum2 += (per+i)->payout;
	}
	return sum1+sum2;
}



/*	�������ܣ��˵�ģ��
������������
��������ֵ����
*/
void Menu()
{
	printf("1.Input One deal\n");
	printf("2.Print All the Balance\n");
	printf("3.Print One year Balance\n");
	printf("4.Exit to DOS\n");
}
char bioskey()
{
	char choice[10];
	scanf("%1s",choice);
	return choice[0];
}
/*	�������ܣ����ͳ�ƣ������������ܶ֧���ܶ���
�����������ṹ��ָ�����per������ָ��ṹ�������ָ��
                      ���ͱ���year��������ȣ���2004
��������ֵ����
*/
void OneYearBalance(FINANCE *per,int year)
{
	int i;
	double sum1 = 0.0,sum2 = 0.0;

	for(i=0;i<DEAL;i++)
	{
		if((per+i)->dt.da_year != year)continue;

		sum1 += (per+i)->earning;
		sum2 += (per+i)->payout;
	}
	printf("param of %d  : \n ",year);
	printf("Sum of earning       Sum of payout        Balance\n");
	printf("%15.2f%20.2f%15.2f\n",sum1,sum2,sum1+sum2);
}
/*	�������ܣ���ӡ���еĽ�����Ϣ
�����������ṹ��ָ�����per������ָ��ṹ�������ָ��
��������ֵ����
*/
void PrintBalance(FINANCE *per)
{
	int i;
	printf("  Date       Time      Earning     Payout    Balance \n");
	printf("-----------------------------------------------------\n");
	for(i=0;i<DEAL;i++)
	{
		if((per+i)->dt.da_year != 0)
		{
			printf("%d/%2d/%2d  ",(per+i)->dt.da_year,
				(per+i)->dt.da_mon,(per+i)->dt.da_day);
			printf("%02d:%02d:%02d  ",(per+i)->ti.ti_hour,
				(per+i)->ti.ti_min,(per+i)->ti.ti_sec);
		}
		if((per+i)->earning!=0)
			printf("%8.2f\n",(per+i)->earning);
		if((per+i)->payout!=0)
			printf("            %8.2f\n",(per+i)->payout);
	}
	printf("-----------------------------------------------------\n");
	printf("                                             %8.2f\n",	Balance(per));
}

/*	�������ܣ���ӡĳһ��Ľ�����Ϣ
�����������ṹ��ָ�����per������ָ��ṹ�������ָ��
��������ֵ����
*/
void PrintOneYear(FINANCE *per)
{
	int i,year;
	printf("Please Input one year :");
	scanf("%d",&year);
	printf("  Date       Time      Earning     Payout    \n");
    printf("----------------------------------------------\n");
	for(i=0;i<DEAL;i++)
	{
		if((per+i)->dt.da_year != year) continue;

		if((per+i)->dt.da_year!=0)
		{
			printf("%d/%02d/%d  ",(per+i)->dt.da_year,
				(per+i)->dt.da_mon,(per+i)->dt.da_day);
			printf("%02d:%02d:%02d   ",(per+i)->ti.ti_hour,
				(per+i)->ti.ti_min,(per+i)->ti.ti_sec);
		}
		if((per+i)->earning!=0)
			printf("%8.2f\n",(per+i)->earning);
		if((per+i)->payout!=0)
			printf("            %8.2f\n",(per+i)->payout);
	}
    printf("----------------------------------------------\n");
   printf("\n");
	OneYearBalance(per,year);
}

