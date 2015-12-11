#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100  
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

//定义循环链表的存储结构
typedef int Status; 
typedef struct LNode
{
    int id;         //第几个人
	int pawd;       //密码 
    struct LNode *next;   //指针域 
}LNode;  
typedef struct LNode *LinkList;

//1.定义一个创建结点的方法
LNode *GetNode(int pid,int ppawd)
{
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	if(!p)return ERROR;
	p ->id = pid;
	p ->pawd = ppawd;
	p ->next = NULL;
	return p;
} 

//2.创建循环单链表
Status ListCreate(LinkList L,int n)
{
	int i,ppawd;
	LinkList p,q;
	for(i = 1;i <= n;i++)
	{
		printf("请输入第%d个人持有的密码：",i);
		scanf("%d",&ppawd);
		p = GetNode(i,ppawd);
		if(L == NULL)
		{
			L = q = p;
			q ->next = L;
		}else{
			p ->next = q ->next;
			q ->next = q;
			q = p;
		}
	}	
	printf("完成单向循环链表的创建!\n");
	return OK;
}  

//3.判断循环单链表是否为空
Status ListEmpty(LinkList L)
{
	if(!L)return TRUE;
	return FALSE;
} 

//4.打印循环链表当前的所有元素
void ListPrint(LinkList L)
{
	LinkList p = L;
	if(ListEmpty(L))return;
	do{
		printf("第%d个人的密码为：%d\n",p ->id,p ->pawd);
		p = p ->next;
	}while(p != L);
	getchar();
} 

//5.开始游戏
void StartGame(LinkList L,int startpawd)
{
	int i,isFlag = 1;
	LinkList p,q,r;
	p = q = L;
	//让p指向尾部结点，为删除做准备
	while(p ->next != L)p = p ->next;
	while(isFlag)
	{
		for(i = 1;i < startpawd;i++)
		{
			p = q;
			q = q ->next;
		}
		if(p == q)isFlag = 0;
		r = q;  //删除q指向的结点，有人出列
		p ->next = q ->next;
		q = q->next;
		startpawd = q ->pawd;
		printf("第%d个人出列，他手持的密码是：%d\n",r ->id,r ->pawd);
		free(r); 
	} 
	L = NULL;
	getchar();
} 



int main()
{
	int n, m;
 	LinkList L = NULL;
 	while(1)
 	{
	  printf("请输入人数n（最多%d个）: ", MAX_SIZE);  
        scanf("%d", &n);         
        printf("和初始密码m: ");  
        scanf("%d", &m);  
        if (n > MAX_SIZE)  
        {  
            printf("人数太多，请重新输入！\n");  
            continue;  
        }  
        else  
            break;  	
 	}
 	ListCreate(L,n);
    printf("\n------------ 循环链表原始打印 -------------\n");  
    ListPrint(L);  
    printf("\n-------------删除出队情况打印 -------------\n");  
    StartGame(L, m);  
	return 0;
}