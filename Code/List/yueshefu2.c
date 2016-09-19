#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//定义循环链表的存储结构
typedef struct LNode
{
    int data;         //数据域
    struct LNode *next;   //指针域 
}LNode;  
typedef struct LNode *LinkList;

//定义循环链表的初始化方法
LinkList createList(int n)
{
	printf("\n初始化循环链表\n\n"); 
	LinkList head,s,p;
	int i = 1;
	head = (LinkList)malloc(sizeof(LNode));
	p = head;
	if(n != 0)
	{
		while(i <= n)
		{
			s = (LinkList)malloc(sizeof(LNode));
			s ->data = i++;
			p ->next = s;
			p = s;
		}
		 s->next = head->next;  
	}
    free(head);  
    return s->next;  
}



int main()
{
	int n,m,i;
	printf("输入参加的人数:\n");  
    scanf("%d",&n);  
    printf("输入每隔多少死一个人:\n");  
    scanf("%d",&m);
	LinkList p = createList(n);
	LinkList temp;
	m %= n;  //为了防止报数的人大于参与的人，求余可以理解为重头开始
	while(p != p ->next)
	{
		for(i = 1;i < m -1;i++)
		{
			p = p ->next; 
		}
		printf("第%d个人自杀了\t",p ->next->data);
		temp = p ->next;
		p ->next = temp ->next;
		free(temp);
		p = p ->next; 
	} 
	printf("\n第%d个人活下来了！\n\n", p->data );    
    return 0;  
}
