#ifndef _LIST_H
#define _LIST_H

typedef struct _NODE
{
	void* data;
	struct _NODE* next;
}NODE, *PNODE;

typedef struct _LIST
{
	void* list_data;
	PNODE first;
}LIST, *PLIST;


/***  ����һ���µ�����  ***/
PLIST ListCreate(void* list_data);

/***  ����ڵ㵽����   ***/
int ListInsertAt(PLIST list, unsigned int n, void* data);

/***  ������ͷ������ڵ�   ***/
void ListPushFront(PLIST list, void* data);

/***  ������β������ڵ�   ***/
void ListPushBack(PLIST list, void* data);

/***  ɾ������ͷ���ڵ�   ***/
void* ListPopFront(PLIST list);

/***  ɾ������β���ڵ�   ***/
void* ListPopBack(PLIST list);

/***  ������Ż�ýڵ�   ***/
void* ListGetAt(PLIST list, unsigned int n);

/***  �������ɾ���ڵ�   ***/
void* ListDeleteAt(PLIST list, int n);

/***  ɾ�������е����нڵ�   ***/
void ListClearAndFree(PLIST list);

/***  ɾ����������   ***/
void ListDistory(PLIST list);

/***  ɾ�����������������е�ȫ���ͷ�   ***/
void ListDistoryAndFree(PLIST list);

/***  ��õ�ǰ�����С���ڵ�������   ***/
int ListSize(PLIST list);


#endif // !_LIST_H