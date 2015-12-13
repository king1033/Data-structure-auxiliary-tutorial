#include <stdio.h>
#include <stdlib.h>

#define CARD_NUM 13

typedef struct LNode
{
	int data;         
	struct LNode *next;   
}LNode;  
typedef struct LNode *LinkList; 

//定义一个初始化链表的方法
LinkList ListCreate()
{
	LinkList head = NULL,p,q = head;
	int i;
	for(i = 1;i <= CARD_NUM;i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		p ->data = 0;
		if(head == NULL)head = p;
		else q ->next = p;
		q = p;
	}
	q ->next = head;
	return head;
} 

//计算发牌顺序
void deal(LinkList L)
{
	LinkList p;
	int j;
	int countNum = 2;
	p = L;
	p ->data = 1;
	while(1)
	{
		for(j = 0;j <countNum;j++)
		{
			p = p ->next;
			if(p ->data != 0)
			{
				p ->next;
				j--;
			}
		}
		if(p->data == 0)
		{
			p ->data = countNum;
			countNum++;
			if(countNum == 14)break;
		}
	}
} 


int main()
{
	LinkList p = NULL;
	int i;
	p = ListCreate();
	deal(p);
	printf("牌的放置顺序为：\n\n");
	for(i = 0;i < CARD_NUM;i++)
	{
		printf("黑桃%d\t",p ->data);
		p = p ->next;
	}
	printf("\n\n");
	return 0;
}
