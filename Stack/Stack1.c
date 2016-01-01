#include <stdio.h>

#define STACK_INIT_SIZE 10 //存储空间的初始分配量
#define STACK_INCREMENT 2 //分配增量 

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int SElemType;
typedef int Status;
typedef struct LNode
{
	SElemType *base;  //栈底指针变量 
	SElemType *top;  //栈顶指针变量 
	int stacksize;  //当前可试用的最大容量 
}LNode;
typedef LNode *SqStack;

//1.构造空栈
void InitStack(SqStack S)
{
	S ->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S->base)exit(ERROR);
	S ->top = S ->base;  //栈顶指向栈底
	S ->stacksize = STACK_INIT_SIZE; 
} 

//2.将栈置空
void ClearStack(SqStack S)
{
	S ->top = S ->base;  //栈顶指向栈底 
} 

//3.判断是否为空栈
int StackEmpty(SqStack S)
{
	return S ->top == S ->base?TRUE:FALSE;
} 

//4.销毁栈
void DestoryStack(SqStack S)
{
	free(S ->base); //释放栈空间
	S ->top = S ->base = NULL;  //将栈顶和栈底设置为NULL 
	S ->stacksize = 0;     //存储空间设置为0 
} 

//5. 获得栈中的元素个数
int StackLength(SqStack S)
{
	return S ->top - S ->base;
} 


//6.获得栈顶元素
Status GetTop(SqStack S,SElemType *e)
{
	if(S ->top > S ->base)
	{
		e = S ->top - 1;
		return OK;
	}else{
		return ERROR;
	}
}

//7.往栈中插入元素(压栈)
void PushStack(SqStack S,SElemType e) 
{
	//判断当前栈容量是否满了，满了需要增加空间 
	if(S ->top - S ->base == S ->stacksize)	
	{
		S ->base = (SElemType *)realloc(S ->base,
		     (S ->stacksize + STACK_INCREMENT)*sizeof(SElemType));
  		if(!S->base)exit(ERROR);
  		S ->top = S ->base + S ->stacksize;  //修改栈顶指针指向新的栈顶
		S ->stacksize += STACK_INCREMENT;   //更新容量 
	}
	*(S ->top ++) = e; 
}

//8.弹出栈中的元素
 Status PopStack(SqStack S,SElemType e) 
 {
 	if(S ->top == S ->base)return ERROR;  //栈为空
	e = *(--S ->top);   //栈顶元素值付给e,栈顶指针下移 
	return OK;  	
 }
 
 //9.遍历栈中的元素
 void StackTraverse(SqStack S,void *visit(SElemType))
 {
 	//从栈底开始到栈顶 
 	while(S ->top > S ->base)
 	visit(*(S ->base ++));
 	printf("\n");
 }

int main()
{
	printf("呵呵");
	return 0;
}