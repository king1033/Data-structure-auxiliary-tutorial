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
typedef struct LNode *LinkList; //定义两个只是方便使用而已~ 

//1.构建一个空表 
LinkList InitList()
{
	LinkList L;
	L = (LinkList)malloc(sizeof(LNode));
	if(!L)exit(ERROR);
	else L ->next = L ->prior = L;
	return L;
} 

//2.将表置空
void ClearList(LinkList L)
{
	LinkList p = L ->next;   //指向第一个结点 
	while(p != L)
	{
		p = p ->next;  //指向下一个结点 
		free(p->prior); //释放该结点的前驱结点 
	}
	L ->next = L ->prior = L; //自己指自己 
} 

//3.判断是否为空表 
Status ListEmpty(LinkList L)
{
	return L->next == L && L ->prior == L?TRUE:FALSE;
}

//4.销毁表
void DestoryList(LinkList L)
{
	ClearList(L);
	free(L);
	L = NULL;
}

//5.获得表长度
int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L ->next;
	while(p != L)
	{
		i++;
		p = p ->next;
	}
	return i;
} 

//6.获得表中第i个元素的值
Status GetElem(LinkList L,int i,ElemType *e)
{
	int j = 1;
	LinkList p = L ->next;  //指向第一个结点
	while(p != L && j < i)   //指针后移 
	{
		j++;
		p = p ->next;
	} 
	if(p == L || j > i)return ERROR;  //找不到该元素
	e = p ->data;
	return OK; 	
}

//7.查找表中是否存在满足条件的元素
int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType)) 
{
    int i = 0;
    LinkList p = L ->next ->next;  //指向第一个结点
    while(p != L ->next)
    {
        i++;
        if(compare(p->data,e))return i;
        p = p ->next; 
    } 
    return 0;   //找不到，返回0 
}

//8.获得某个节点的直接前驱
Status BeforeElem(LinkList L,ElemType choose,ElemType *before)
{
	LinkList p = L ->next ->next;  //指向第二个结点
	while(p != L)
	{
		if(p ->data == choose)
		{
			before = p ->prior ->data; 
			return OK;
		}
		p = p ->next;
	} 
	return ERROR;
}

//9.获得某个节点的直接后继
Status NextElem(LinkList L,ElemType choose,ElemType *behind)
{
	LinkList p = L ->next ->next; //指向第二个结点
	while(p != L)
	{
		if(p ->prior ->data == choose)
		{
			behind = p ->data;
			return OK;
		}
		p = p ->next;
	} 
	return ERROR;
}


//10.返回第i个元素的地址
LinkList GetElemAdd(LinkList L,int i)
{
	int j;
	LinkList p = L;
	if(i < 0 || i > ListLength(L))return NULL; //判断i值位置是否合法
	for(j = 1;j <= i;j++)
	{
		p = p ->next;
	} 
	return p;
}                              


//11.往第i个位置插入元素
Status ListInsert(LinkList L,int i,ElemType e)
{
	LinkList p,q;
	//判断i值是否合法
	if(i < 1 || i > ListLength(L) + 1)return ERROR;
	p =  GetElemAdd(L,i - 1);
	//NULL的话说明，第i个结点的前驱不存在，
	//这里假设头节点为第一个结点的前驱 	 
	if(!p)return ERROR; 
	q = (LinkList)malloc(sizeof(LNode));
	if(!q)return ERROR;
	q ->data = e;  //给新结点赋值
	q ->prior = p;  //新结点的前驱为第i - 1个结点
	q ->next = p ->next; //新结点的后记为第i个结点
	p ->next ->prior = q; //第i个结点前驱指向新结点 
	p ->next = q;  //第i-1个结点的后继指向新结点 
	return OK; 
}

//12.删除第i个位置的元素
Status ListDelete(LinkList L,int i,ElemType *e)
{
	LinkList p;
	if(i < 1)return ERROR; //判断删除位置是否合法
	p = GetElemAdd(L,i);
	if(!p)return ERROR;  //为NULL说明第i个元素不存在
	e = p ->data;
	p ->prior ->next = p ->next; //i-1个结点的后继指向滴i+1个结点
	p ->next ->prior = p ->prior; //第i+1个结点的前驱指向第i - 1个结点
	free(p); //释放第i个结点
	return OK; 
}



int main()
{
	LinkList p;
	p = InitList();
	printf("%d\n",ListLength(p));
	return 0;
}