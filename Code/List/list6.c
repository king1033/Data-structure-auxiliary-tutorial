#include <stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;  
typedef int Status;
typedef struct LNode
{
	ElemType data;         //数据域
	struct LNode *prior;   //前驱指针 
	struct LNode *next;   //后继指针
	 
}LNode;  
typedef struct LNode *LinkList;

//定义一个创建N个结点的方法
 LinkList ListCreate(int N)
 {
 	LinkList p,q,head;
 	int i,data;
 	q = head;
 	head = (LinkList)malloc(sizeof(LNode));	
 	head ->prior = head;
 	head ->next = head;
 	p = head;
 	for(i = 0;i < N;i++)
 	{
	 	printf("请输入第%d个结点的值：",i + 1);
	 	scanf("%d",&data);
	 	q = (LinkList)malloc(sizeof(LNode));
	 	q ->data = data;
	 	p ->next = q;
	 	q ->prior = p;
		q ->next = head; 
		head ->prior = q; 
		p = q; 
 	}
 	return head;
 } 
 
 //定义一个打印结点数据的方法
 void PrintNode(ElemType e)
 {
 	printf("%d\t",e);
 } 
 
 //定义一个正序输出链表的方法
 void ListTraverse(LinkList L)
 {
 	LinkList p = L->next;  //指向首元结点
	while(p!=L)
	{
		PrintNode(p->data);
		p = p ->next;
	} 
	printf("\n");
 } 
 
 //定义一个逆序输出链表的方法
 void ListTraverseBack(LinkList L)
 {
 	LinkList p = L ->prior;  //指向最后一个结点 
	while(p!=L)
	{
		PrintNode(p->data);
		p = p ->prior;
	} 
	printf("\n");
 } 
 
 
 int main()
 {
 	LinkList p;
 	int N = 0;
 	printf("请输入双向链表的结点个数：");
 	scanf("%d", &N);
 	p = ListCreate(N);
 	printf("正序打印链表中的结点：\n");
 	ListTraverse(p);
 	printf("逆序打印链表中的结点：\n");
 	ListTraverseBack(p); 
 	return 0;
 }