#include <stdio.h>
#include<malloc.h>


#define MAXSIZE 20
#define INCREMENT 10
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//定义一个int数据类型的别名  
//这里因为演示采用int,实际使用的通常是复合的数据类型 
typedef int ElemType;  
typedef int Status;
typedef struct{
	ElemType *elem;   //存储空间的起始地址
	int length;       //表的当前长度
	int listsize;     //表的总存储容量(sizeof(ElemType)) 
}SqList;

void printList(SqList L);
void InitList(SqList *L);
Status ListInsert(SqList *L,int i,ElemType e);

int main(int argc, char *argv[])
{
	SqList list;
	ElemType c;
	InitList(&list);
	int i;
	for(i = 1;i <= 11;i++){
		ListInsert(&list,i,i * 2);	
	}
	printf("插入后的表：\n");
	printList(list);
	ListDelete(&list,2,&c);
	printf("删除后的表：\n"); 
	printList(list);
	printf("Hello C-Free!\n");
	return 0;
}



//1)创建一个空表 
void InitList(SqList *L){
	L -> elem = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
	if(!L -> elem)exit(ERROR);
	L -> length = 0;
	L -> listsize = MAXSIZE;
}

//2)将表置为空表
void ClearList(SqList *L)  
{  
    L ->length = 0;  
}

//3)判断表是否为空
Status ListEmpty(SqList L)
{	
	return L.length == 0?TRUE:FALSE;
} 


//4)销毁表
void DestoryList(SqList *L)
{
	free(L ->elem);
	L ->elem = NULL;
	L ->length = 0;
	L ->listsize = 0;
} 

//5)获得当前表中元素的数目  
int ListLength(SqList L)  
{  
    return L.length;   
}

//6)获得表中第i个数据元素的值
Status GetElem(SqList L,int i,ElemType *e)
{
	if(i < 1||i > L.length)return ERROR;
	e = *(L.elem + i - 1);
	return OK; 
}  

//7)查找表中是否有满足要求的元素
//返回表中第一个满足要求的元素的下标  
//这里我们把要求假设为一个函数compare(int l_s,int e);   
//参数依次为表中元素与需要进行关系比较的参数e  
//第三个参数函数指针,指向函数的指针
int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))  
{  
    int i = 1;  
    ElemType *p = L.elem;  
    while(i < L.length && !compare(*p++,e))  
    i++;  
    if(i <= L.length) return i;  
    else return 0;  
}   

//8)返回某个节点的直接前驱
//第二个和第三个参数分别为：指定的数据元素，before用来存储他的前驱的
Status PriorElem(SqList L,ElemType choose,ElemType *before){
	int i = 2;
	ElemType *p = L.elem + 1;
	while(i < L.length && *p != choose)
	{
		p++;
		i++;
	}
	if(i > L.length)return ERROR;
	else
	{
		before = *--p;
		return OK;
	}		
} 


//9.返回某个节点的后继 
//第二三个参数依次为:选定的数据元素的值,存储后继的变量 
Status NextElem(SqList L,ElemType choose,ElemType *behind)
{
	int i = 0;
	ElemType *p = L.elem; 
	while(i < L.length && *p != choose)
	{
		p++;
		i++; 
	} 
	if(i == L.length)return ERROR;
	else{
		behind = * ++p;
		return OK;
	}
}

//10.往表中第i个位置插入元素
Status ListInsert(SqList *L,int i,ElemType e)
{
	ElemType *p,*q,*newbase;
	//判断插入位置是否合法
	if(i < 1 || i > L -> length + 1)return ERROR;
	//假如表满了的话，增加分配的空间 
	if(L -> length == L -> listsize)
	{
		newbase = (ElemType *)realloc(L -> elem,(L -> listsize + INCREMENT)*sizeof(ElemType));
		if(!newbase)exit(ERROR);
		L ->elem = newbase;
		L ->listsize += INCREMENT;
	} 
	//插入位置 
	q = L ->elem + i - 1;
	//向右移，先移动最后一个
	for(p = L ->elem + L->length - 1;p >= q;--p)
	{
		*(p + 1) = *p;	 
	} 
	*q= e;      //插入元素 
	++L->length;   //表长 + 1  
	return OK;
}
 
 
//11.删除表中的第i个位置的元素
Status ListDelete(SqList *L,int i,ElemType *e)
{
	ElemType *p,*q;
	//判断删除的位置是否合法
	if(i < 1 || i > L ->length)return ERROR;
	//P指针指向删除位置，将要删除的元素赋值给e
	p = L ->elem + i - 1;
	e = *p;
	//q指针指向最后一个元素，从删除位置后的元素开始左移
	q = L ->elem + L ->length - 1;
	for(++p;p <= q;++p)
	{
		*(p - 1) = *p;		
	} 
	L ->length--; //表长-1	
	return OK;	
} 

//12.遍历表中的所有元素
void ListTraverse(SqList L,void(* visit)(ElemType))
{
 	int i;
 	ElemType *p = L.elem;
 	for(i = 1;i < L.length;i++)
 	{
 		visit(*p++);
 		printf("\n");
 	}
}

//打印表中所有的元素
void printList(SqList L){
	int i;
	ElemType *p = L.elem;
	for(i = 1;i< L.length;i++)
	{
		printf("表中的第%d个元素的值为：%d\n",i,*p++);
	}
} 



//应用小示例：求两个表的并集
void UnionList(SqList La,SqList Lb,SqList *Lc)
{
	//1.定义指向表A,B表头，表尾的指针
	ElemType *la,*la_end,*lb,*lb_end,*lc;
	la = La.elem;
	lb = Lb.elem;
	la_end = La.elem + La.length - 1;
    lb_end = Lb.elem + Lb.length - 1;
    //2.为表C分配内存空间，大小为表A长度 + 表B的长度
	Lc ->listsize  = La.length + Lb.length;
	lc = Lc ->elem = (ElemType *)malloc(Lc ->listsize * sizeof(ElemType));
	if(!lc)exit(ERROR);
	//3.将表A和B中的元素进行合并， 
	while(la <= la_end && lb <= lb_end)
	{
		if(*la <= *lb)*lc++ = *la++;
		else *lc++ = *lb++;
	} 
	//4.假如有剩余的元素，要么是表A,要么是表B的
	while(la < la_end)*lc++ = *la++;
	while(lb < lb_end)*lc++ = *lb++;
	//5.接着要将C表中重复的元素删除掉，这里来两枚指针 
	ElemType *p,*q;
	p = Lc ->elem;
	q = p;
	//6.循环，假如入指针p没有指向表尾
	while(p != (Lc ->elem + Lc ->length - 1))
	{
		//q指向p的后继元素，比较两数的值
		if(*p != *(++q))
		{
			p++;
			q = p;
		} 
		//相等的话，删除q所指向的元素
		else
		{
			while(*p == *q);
		//	ListDelete(Lc,(p - Lc ->elem),e);
		} 
	} 
}