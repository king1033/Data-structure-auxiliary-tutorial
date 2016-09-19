#include <stdio.h>
#include <stdlib.h>


typedef struct LNode
{
	int data;         
	struct LNode *next;   
}LNode;  
typedef struct LNode *LinkList; 

//定义一个初始化链表的方法
LinkList ListCreate(int n)
{
	LinkList head = NULL,p,q = head;
	int i;
	for(i = 1;i <= n;i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		p ->data = i;
		if(head == NULL)head = p;
		else q ->next = p;
		q = p;
	}
	q ->next = head;
	return head;
} 

int main()
{
	LinkList p,q;
	int i,num = 0;
	printf("请输入您要构建的拉丁方针的规模(比如3*3，输入3即可)\n");
	scanf("%d",&num);
	p = ListCreate(num);
	printf("%d * %d 的拉丁方阵构建完毕，输出结果：\n\n",num,num);
	for(i = 0;i < num;i++)
	{
		q = p;
		while(1)
		{
			printf("%d  ",p ->data);
			p = p ->next;
			if(p == q)break;  //已经走完一轮了 
		}
		p = p ->next; 
		printf("\n");
	}
	printf("拉丁方阵打印完毕~~\n\n");
	return 0;
}
