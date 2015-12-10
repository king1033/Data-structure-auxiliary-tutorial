#include <stdio.h>
#include<malloc.h>


#define MAXSIZE 100
#define INCREMENT 10
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;  
typedef struct LNode
{
	ElemType data;         //数据域
	struct LNode *next;   //指针域 
}LNode;  
typedef struct LNode *LinkList;

int main()
{
	LinkList list;
	InitList(list);
	int i = ListLength(list);
	printf("%d\n",i);
	return 0;
}


//1)创建空表 
Status InitList(LinkList L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if(!L)exit(ERROR);
	L ->next = L;   //自己指自己~（头节点指针域指向头结点） 
	return OK;
}

//2）将表置空
void ClearList(LinkList L)
{
	LinkList p,q;
	L = L ->next;     //指向头结点 
	p = L ->next;    //指向第一个结点 
	while(p!=L)
	{
		q = p ->next;
		free(p);
		p = q;
	}
	L ->next = L; //自己指自己 
} 

//3）判断是否为空表(有头节点的情况) 
Status ListEmpty(LinkList L)
{
	return L!=L ->next?FALSE:TRUE; 
}

//4）销毁表
void DestoryList(LinkList L) 
{
	ClearList(L);  //将表置空
	free(L);    //释放头节点 
	L = NULL; 
}

// 5）获得表长度
int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L ->next;  //指向头结点 
	while(p != L)
	{
		i++;
		p = p ->next;
	} 
	return i;
} 

// 6）获得表中第i个元素的值
Status GetElem(LinkList L,int i,ElemType *e)
{
	int j = 1;
	LinkList p = L ->next ->next;	//指向第一个结点
	if(i <= 0||i >ListLength)return ERROR;  //判断插入位置是否合法 
	while(j < i)
	{
		j++;
		p = p ->next;
	} 
	e = p ->data;
	return OK;
} 

//7)查找表中是否存在满足条件的元素
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

//8）获得某个节点的直接前驱
Status BeforeElem(LinkList L,ElemType choose,ElemType *before)
{
	LinkList q,p = L ->next ->next;  //指向第一个结点
	q = p ->next;  
	while(q != L ->next)
	{		
		if(q ->data == choose)
		{
			before = p ->data;
			return OK;
		}
		p = q; //继续后移
		q = q ->next; 
	}
	return ERROR;  	
}


//9）获得某个节点的直接后继
Status NextElem(LinkList L,ElemType choose,ElemType *behind)
{
	LinkList p = L ->next ->next;  //指向第一个结点
	while(p != L)
	{
		if(p ->data == choose)
		{
			behind = p ->next ->data;
			return OK;
		}
	}
}

//10）往第i个位置插入元素
Status ListInsert(LinkList L,int i,ElemType e)
{
	LinkList s,p = L ->next;
	int j = 0;
	if(i <= 0 || i > ListLength(L) + 1)return ERROR;  //判断插入位置是否合法
	//寻找插入结点的前一个结点 
	while(j < i - 1) 
	{
		j++;
		p = p ->next;	
	}
	//生成新结点
	s = (LinkList)malloc(sizeof(LNode)); 
	s ->data = e; //将e赋值给新结点
	s ->next = p ->next; //新结点指向原来的第i个结点 
	p ->next = s;   //原i - 1个结点指向新结点 
	//假如插入的位置是表尾，把新的表尾地址给尾指针 
	if(p == L)
	{
		L = s;
	}
	return OK;
} 


//11）删除表中第i个元素
Status ListDelete(LinkList L,int i,ElemType *e)
{
	LinkList s,p = L ->next;
	int j = 0;
	if(i <= 0||i > ListLength(L))return ERROR;//判断删除位置是否合法 
	//寻找插入结点的前一个结点 
	while(j < i - 1) 
	{
		j++;
		p = p ->next;
	}
	s = p ->next;
	p ->next = s ->next; 
	e = s ->data;
	if(s == L)
	L = p;
	free(q);  //释放结点
	return OK; 
}


//12）遍历循环链表里的所有元素
void ListTraverser(LinkList L,void(*visit)(ElemType))
{
	LinkList p = L ->next ->next;   //指向第一个结点 
    while(p != L ->next)
    {
        visit(p ->data);
        p = p ->next;
    }
    printf("\n");
}
