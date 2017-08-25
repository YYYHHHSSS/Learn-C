#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
typedef struct Date
{
int day;
int month;
int year;
}Date;

typedef struct Family /* Family structure declaration */
{
struct Date dob;
char name[20];
char father[20];
char mother[20];
struct Family *next; /* Pointer to next structure */
struct Family *previous; /* Pointer to previous structure */
}Family;

Family *get_person(void); /* ��ȡ��ͥ��Ա��Ϣ�����������ָ��*/
void show_people(int forwards,Family *pfirst,Family *plast); /* ��ʾ��ͥ��Ա��Ϣ����һ������forwards��ʾ�����Ƿ��������ֵΪ1ʱ�����������ֵΪ0ʱ������������������������������е�һ�������һ��family����ĵ�ַ*/
void release_memory(Family *pfirst);/*�ṩ�����е�һ��Family����ĵ�ַ���ú����Ϳ��Ա��������е�����Ԫ�أ��ͷ�����ռ�õ��ڴ档*/

int main(void)
{
struct Family *first = NULL; /* Pointer to first person */
struct Family *current = NULL; /* Pointer to current person */
struct Family *last = NULL; /* Pointer to previous person */
char more = '\0'; /* Test value for ending input */

while(1)
{
// printf("\nDo you want to enter details of a%s person (Y or N)? ",
// first != NULL?"nother" : "");

scanf(" %c", &more);
if(tolower(more) == 'n')
break;

current = get_person();

if(first == NULL)
{
first = current; /* Set pointer to first Family */
}
else
{
last->next = current; /* Set next address for previous Family */
current->previous = last; /* Set previous address for current */
}
last = current;/* Remember for next iteration */
}
printf("\nShow in a forward way.\n");
show_people(1, first, last);
printf("\nShow in a reverse way.\n");
show_people(0, first, last);
release_memory(first);
first = last = NULL;

return 0;
}
Family *get_person(void)
{
	Family *p1;
	char ch;
	p1 = (Family *)malloc(sizeof(Family));
	while ((ch=getchar())!='\n'&&ch!=EOF) ;
	gets_s(p1->name);
	scanf("%d %d %d", &(p1->dob.day), &(p1->dob.month), &(p1->dob.year));
	getchar();
	gets_s(p1->mother);
	gets_s(p1->father);
	p1->previous = NULL;
	p1->next = NULL;
	return p1;
}
void show_people(int forwards, Family *pfirst, Family *plast)
{
	Family *p;
	if (forwards)
	{
		p=pfirst;
		while (p!=NULL)
		{
			printf("\n%s was born %d/%d/%d, and has %s and %s as parents.\n", p->name, p->dob.day, p->dob.month, p->dob.year, p->mother, p->father);
			p = p->next;
		}
	}
	else
	{
		p=plast;
		while (p!=NULL)
		{
			printf("\n%s was born %d/%d/%d, and has %s and %s as parents.\n", p->name, p->dob.day, p->dob.month, p->dob.year, p->mother, p->father);
			p = p->previous;
		}
	}
}
void release_memory(Family *pfirst)
{
	Family *p;
	while (pfirst)
	{
		p = pfirst;
		pfirst = pfirst->next;
		free(p);
		p=NULL;
	}
}