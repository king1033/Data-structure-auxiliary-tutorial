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
typedef struct
{
   ElemType data;   //数据
   int cursor;           //游标
}Component,StaticLinkList[MAXSIZE];   //使用数组下标标识每个节点

//1.初始化静态链表 
Status InitList(StaticLinkList space)
{
	int i;
	for(i = 0;i < MAXSIZE - 1;i++)
	{
		//每个游标指向下一个下标,
		//比如第0个游标指向第一个下标结点 
		//第一个结点的游标指向第二个下标结点 
		space[i].cursor = i+1;          			
	}
	//最后一个结点需要结点的游标设置为0 
	space[MAXSIZE - 1].cursor = 0;	
	return OK;
}

//2.获得备用链表的结点下标
int GET_Free(StaticLinkList space)
{
	int i = space[0].cursor;  
    //设置下一个结点为备用结点  
	if(space[0].cursor)
		space[0] = space[i].cursor;  
	return i;
} 

//3.获得静态链表中的元素个数
int GetLength(StaticLinkList L)
{
	int j = 0;
	int i = L[MAXSIZE - 1].cursor;  //指向第一个链表的游标 
	while(i)
	{
		i = L[i].cursor;
		j++;
	}
	return j;
} 



//3.往静态链表中插入元素
Status ListInsert(StaticLinkList L,int i,ElemType e)
{
	int j,k,l;
	k = MAXSIZE - 1;  //数组的最后一个元素 
	//①判断插入位置是否合法
	if(i < 1 || i >GetLength(L) + 1)
	{
		return ERROR;
	} 
	//②获取空白结点的数据域
	j = GET_Free(L);
	if(j)
	{
		for(l = 1;l <= i - 1;i++)
		{
			//得到第i - 1个元素的下标
			//注意：不能直接用K = L[K - 1].cursor，因为元素可能是不相邻的
			k = L[k].cursor; 
		} 
		L[j].cursor = L[k].cursor;
		L[k].cursor = j;
		L[0].cursor = GetLength(L) + 1;  //让下标0的元素指向新的空白结点 
		return OK;
	}
	return ERROR;
}


//4.删除静态链表中的第i个元素
Status ListDelete(StaticLinkList L,int i,ElemType e) 
{	
	int j = 0;
    if(i < 1 || i > ListLength(L))return ERROR;  //判断删除位置是否合法
    int k = MAXSIZE - 1;   //获取最后一个节点,因为它的cursor指向第一个有效结点
    //获取第i - 1个元素的下标
	for(j = 1 ; j < i ; ++j)                      
    {
		k = L[k].cursor   ;
	}
    j = L[k].cursor ;    //得到第i个元素的下标
    L[k].cursor = L[j].cursor ;  //将删除节点的cursor赋值给前一个结点
    Free_Node(L,j);     //释放到第i个元素,下标为j
    return OK;
}

//5.将下标为k的空闲结点回收为备用结点
void FreeNode(StaticLinkList space,int k)
{
	space[k].cursor = space[0].cursor;   //将之前的备用链表的第一个结点下标存放到L[k]的cursor中
	space[0].cursor = k;  //下标为k的元素称为第一个空闲结点
} 

 

