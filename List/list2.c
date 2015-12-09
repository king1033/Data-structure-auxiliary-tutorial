#include <stdio.h>
#include<malloc.h>


#define MAXSIZE 20
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
typedef struct LNode *LinkList; //定义两个只是方便使用而已~ 


int main(int argc, char *argv[])
{
	return 0;
}

//头插法建链表 
void HeadCreateList(LinkList L,int n)
{
	LinkList p;
	int i;
	srand(time(0));    //初始化随机数种子
	L = (LinkList)malloc(sizeof(LNode));
	L ->next = NULL;
	//利用循环生成结点并添加到单链表中 
	for(i = 0;i < n;i++)
	{
		p = (LinkList)malloc(sizeof(LNode));    //生产新结点 
		p ->data = rand()%100 + 1;              //生产两位随机数100,三位就是1000 
		p ->next = L ->next;    
		L ->next = p;                      //插到表头 
	}	
}

//尾插法建链表 
void TailCraeteList(LinkList L,int n)
{
	LinkList p,r;
    int i;
    srand(time(0));    //初始化随机数种子
	L = (LinkList)malloc(sizeof(LNode));
	r = L;
	for(i = 0;i < n;i++)
	{
		p = (LinkList)malloc(sizeof(LNode));    //生产新结点 
		p ->data = rand()%100 + 1;              //生产两位随机数100,三位就是1000 
		r ->next = p;        //将表尾终端结点的指针指向新结点 
		r = p;      //将当前的新结点定义为表尾的尾结点 
	}
	r->next = NULL;		 //当前链表结束 
} 

//获取中间结点 
Status GetMidLNode(LinkList *L,ElemType *e)
{
	LinkList p,q;
	p = q = *L;
	while(p ->next ->next != NULL)
	{
		if(p ->next ->next != NULL)
		{
			p = p ->next ->next;
			q = q ->next;
		}else{
			p = p ->next;
		}
	} 
	e = q ->data;
	return OK;
} 


/** 12个基本操作的代码实现：**/ 

//1.创建空的单链表
void InitList(LinkList L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if(!L)exit(ERROR);
	L ->next = NULL;
}

//2.将表置空
void ClearList(LinkList L)
{
	LinkList p = L ->next;
	L ->next = NULL;
	//接着就是释放头结点以外的结点了
	while(p)
	{
		p = L->next;
		free(L);  //释放首元结点
		L = p;    //移动到当前的首元结点 
	} 
} 

//3.判断是否为空表 
Status ListEmpty(LinkList L)
{
	//只需判断头结点的指针域是否为空即可
	if(L ->next)return FALSE;
	else return TRUE;	
}

//4.销毁单链表
void DestoryList(LinkList L)
{
	LinkList q;
	//删除头结点外的结点 
	while(L)
	{
		//指向首元结点，而不是头结点		
		q = L ->next;
		free(L);
		L = q;      //删除后指向首元 
	}
} 

//5.获得表长度 
int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L ->next;
	while(p)
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
	//指向首元，然后依次后移，假如到了结尾或者j的值大于i
	//还没找个改元素说明i不合法
	LinkList p = L ->next;
	while(p && j < i)
	{
		j++;
		p = p ->next;
	} 
	if(!p || j> i)return ERROR;
	e = p ->data;
	return OK;
}

//7.查找表中是否有存在满足条件的元素
int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
	int i = 0;  
    LinkList p = L -> next;  
    while(p)  
    {  
        i++;  
        if(compare(p->data,e))return i;  
        p = p -> next;  
    }  
    return 0;  
} 

//8.获得某个结点的直接前驱
Status BeforeElem(LinkList L,ElemType choose,ElemType *before)
{
	LinkList q,p = L ->next;
	while(p ->next)  //p所指结点有后继 
	{
		q = p ->next;   //q指向p的后继 
		//判断p的后继是否为choose,是的话返回OK,否则继续后移 
		if(q ->data == choose)
		{
			before = p ->data;
			return OK; 
		}
		p = q;		
	}
	return ERROR; 
}

//9.获得某个结点的直接后继
Status NextElem(LinkList L,ElemType choose,ElemType *behind)
{
	LinkList p = L ->next;
	while(p ->next)
	{
		if(p ->data == choose)
		{
			behind = p ->next ->data;
			return OK;
		}
		p = p ->next;
	}
	return ERROR;	
}

//10. 往表中第i个位置插入元素
Status ListInsert(LinkList L,int i,ElemType e)
{
	int j = 0;
	LinkList p,q =L;  //让q指向头结点
	while(p && j < i - 1)
	{
		j++;
		p = p ->next;  //p指向下一个节点 
	}
	if(!p || j > i - 1)return ERROR;
	p = (LinkList)malloc(sizeof(LNode));
	//要先让插入的结点的指针域指向插入位置的后继结点  
    //再让插入节点的前驱的指针域指向插入结点  
    //！！！顺序不能乱哦1   
	p ->data = e;
	p ->next = q ->next;
	q ->next = p;
	return OK;
} 

//11.删除表中第i个元素
Status ListDelete(LinkList L,int i,ElemType *e)
{
	int j = 0;
	LinkList p,q = L;
	while(q ->next && j < i -1)
	{
		j++;
		q = q->next;
	}
	if(!q || j >i -1)return ERROR;
	p = q ->next;   //指向准备删除的结点
	q ->next = p ->next; //删除结点的前驱的指针域指向删除结点的后继   
	e = p ->data; 
	free(p);    //释放要删除的结点  
	return OK;
}


//12.遍历单链表中的所有元素
void ListTraverser(LinkList L,void(*visit)(ElemType))
{
	LinkList p = L ->next;
	while(p)
	{
		visit(p ->data);
		p = p ->next;
	}
	printf("\n");
}